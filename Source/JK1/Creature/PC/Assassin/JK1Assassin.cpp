// Copyright 2024 All Rights Reserved by J&K


#include "JK1Assassin.h"
#include "../../JK1CreatureStatComponent.h"
#include "JK1/Physics/JK1Collision.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Components/TimelineComponent.h"
#include "UObject/ConstructorHelpers.h"



AJK1Assassin::AJK1Assassin()
{
	//Timeline 가져오기
	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("<MyTimeline"));
	
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveRef(TEXT("/Game/Blueprints/Creature/PC/Assassin/CloakCurve.CloakCurve"));
	if (CurveRef.Succeeded())
	{
		FloatCurve = CurveRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKallari/Characters/Heroes/Kallari/Skins/Rogue/Meshes/Kallari_Rogue.Kallari_Rogue'"));
	if (DefaultMesh.Succeeded())
	{
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitEffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonKallari/FX/Particles/Kallari/Abilities/Primary/FX/P_Kallari_Melee_SucessfulImpact.P_Kallari_Melee_SucessfulImpact'"));
	if (HitEffectRef.Object)
	{
		HitEffect = HitEffectRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CloakMaterialRef(TEXT("/Script/Engine.Material'/Game/Blueprints/Creature/PC/Assassin/TPS_Material_Translucnet.TPS_Material_Translucnet'"));
	if (CloakMaterialRef.Succeeded())
	{
		CloakMaterial = CloakMaterialRef.Object;
	}
	

	CreatureStat->SetOwner(true, FName("Assassin"));
	SpawnLocation = FVector(-10.f, 0.f, 50.f); // 캐릭터 앞의 위치
	ThrowDirection = FVector(1.f, 0.f, 0.f); // 앞으로 던지기
	ThrowForce = 1000.f; // 던지기 힘

	// Skill Q 쿨 타임
	SkillQCoolDownTime = 3.0f;
	TimelineValue = 0.0f;
		
}

void AJK1Assassin::BeginPlay()
{
	Super::BeginPlay();
	DynamicMaterial = UMaterialInstanceDynamic::Create(CloakMaterial, this);

	if (FloatCurve)
	{
		FOnTimelineFloat ProgressFunction{};
		ProgressFunction.BindUFunction(this, FName("TimelineProgress"));
		MyTimeline->AddInterpFloat(FloatCurve, ProgressFunction);

		// Timeline 재생 설정
		MyTimeline->SetLooping(false);
		MyTimeline->SetIgnoreTimeDilation(true);
	}
	GetAndStoreMaterials();
}

void AJK1Assassin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWeaponActive)
		CheckWeaponTrace();

	if (MyTimeline)
		MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
}

void AJK1Assassin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJK1Assassin::Attack()
{
	Super::Attack();
}


void AJK1Assassin::ComboActionBegin()
{
	Super::ComboActionBegin();
	
}

void AJK1Assassin::DoCombo()
{
	Super::DoCombo();
	switch (CurrentCombo)
	{
	case 0:
		CurrentCombo = 1;
		PlayAnimMontage(ComboActionMontage1, 1.f);
		break;
	case 1:
		CurrentCombo = 2;
		PlayAnimMontage(ComboActionMontage2, 1.f);
		break;
	case 2:
		CurrentCombo = 3;
		PlayAnimMontage(ComboActionMontage3, 1.f);
		break;
	}
	
}

void AJK1Assassin::ComboActionEnd()
{
	Super::ComboActionEnd();
}

void AJK1Assassin::SkillQ(const FInputActionValue& value)
{
	Super::SkillQ(value);
	UE_LOG(LogAssassin, Log, TEXT("This is %s"), *this->GetName());

	SpawnDagger();
	PlayAnimMontage(SkillQMontage, 1.5f);
	SkillQTrace();	
}

void AJK1Assassin::SpawnDagger()
{
	if (DaggerActor)
	{
		FVector SpawnPoint = GetActorLocation() + SpawnLocation;
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(DaggerActor, SpawnPoint, SpawnRotation, SpawnParams);
		if (SpawnedActor)
		{
			UPrimitiveComponent* ActorPrimitiveComponent = Cast<UPrimitiveComponent>(SpawnedActor->GetRootComponent());
			if (ActorPrimitiveComponent)
			{
				FVector ThrowVector = GetActorForwardVector() * ThrowForce;
				ActorPrimitiveComponent->AddImpulse(ThrowVector, NAME_None, true);
			}
		}
	}
}

void AJK1Assassin::SkillQTrace()
{
	FVector Start = GetActorLocation()+ SpawnLocation;
	FVector End = Start + (GetActorForwardVector() * 1000.f); // 1000 유닛 앞까지 트레이스

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		Start, 
		End, 
		CCHANNEL_JK1ACTION, 
		CollisionParams
	);
	if (bHit)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 3, 0, 3);
		UE_LOG(LogTemp, Warning, TEXT("Pawn Hit: %s"), *HitResult.GetActor()->GetName());
	}
	else 
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3, 0, 3);
	}
}

void AJK1Assassin::OnHit(AActor* Actor, FHitResult& HitResult)
{
	if (Actor)
	{
		FVector HitLocation = HitResult.ImpactPoint;
		FVector ForwardVector = GetActorForwardVector();
		FVector OtherForwardVector = Actor->GetActorForwardVector();

		if (FVector::DotProduct(ForwardVector, OtherForwardVector) > 0)
		{
			if (HitEffect)
			{
				//TODO : 데미지 증가
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitLocation);
			}		
		}
	} 
}

void AJK1Assassin::SpawnHitEffect(const FVector& Location)
{
	if (HitEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Location);
}

void AJK1Assassin::SkillR(const FInputActionValue& Value)
{
	//TODO : 난무 에셋이 어떤건지 잘 모르겠어
}

void AJK1Assassin::SkillLShift(const FInputActionValue& Value)
{
	UE_LOG(LogAssassin, Log, TEXT("This is Assassin Skill LShift"));
	if (IsCloakingProcess)
	{
		UE_LOG(LogAssassin, Log, TEXT("InCloakingProcess"));
		return;
	}
	
	if(!IsCloaking)
	{
		//은신 진입
		IsCloakingProcess = true;
		USkeletalMeshComponent* MeshComponent = GetMesh();

		if (MeshComponent)
		{
			int32 MaterialCount = MeshComponent->GetNumMaterials();
			for (int32 i = 0; i < MaterialCount; i++)
				MeshComponent->SetMaterial(i, DynamicMaterial);
		}

		MyTimeline->PlayFromStart();
		UE_LOG(LogTemp, Log, TEXT("%f"), TimelineValue);
		IsCloakingProcess = false;
		IsCloaking = true;
		GetCharacterMovement()->MaxWalkSpeed = 700.f;
	}
	else
	{
		//은신 해제
		IsCloakingProcess = true;
		MyTimeline->Reverse();
		USkeletalMeshComponent* MeshComponent = GetMesh();
		if (MeshComponent)
		{
			int32 MaterialCount = MeshComponent->GetNumMaterials();
			for (int32 i = 0; i < MaterialCount; i++)
				MeshComponent->SetMaterial(i, StoredMaterials[i]);
		}
		IsCloakingProcess = false;
		IsCloaking = false;
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}

}

void AJK1Assassin::CheckWeaponTrace()
{
	if (!bWeaponActive)
		return;

	FVector StartL = GetMesh()->GetSocketLocation(FName(TEXT("sword_base_l")));
	FVector StartR = GetMesh()->GetSocketLocation(FName(TEXT("sword_base_l")));
	FVector EndL = GetMesh()->GetSocketLocation(FName(TEXT("sword_tip_r")));
	FVector EndR = GetMesh()->GetSocketLocation(FName(TEXT("sword_tip_r")));
	FVector ExtendL = EndL - StartL;
	FVector ExtendR = EndR - StartR;
	const float AttackRadius = 20.f;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);


	bool bSuccessL = GetWorld()->SweepMultiByChannel(
		HitResults,
		StartL,
		EndL,
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		FCollisionShape::MakeCapsule(ExtendL),
		Params
	);

	bool bSuccessR = GetWorld()->SweepMultiByChannel(
		HitResults,
		StartR,
		EndR,
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		FCollisionShape::MakeCapsule(ExtendR),
		Params
	);

	if (bSuccessL || bSuccessR)
	{
		// FDamageEvent DamageEvent;

		for (FHitResult& HitResult : HitResults)
		{
			AActor* Actor = HitResult.GetActor();

			

			if (Actor == nullptr)
				continue;

			if (WeaponAttackTargets.Contains(Actor) == false)
			{
				WeaponAttackTargets.Add(Actor);
				OnHit(Actor, HitResult);
				// TODO HitDamage
				UE_LOG(LogTemp, Log, TEXT("HitDamage: %s"), *Actor->GetName());

			}
		}
	}
#if ENABLE_DRAW_DEBUG
	FVector DirectionL = EndL - StartL;
	FVector DirectionR = EndR - StartR;
	float CapsuleHalfHeightL = DirectionL.Size() / 2.f;
	float CapsuleHalfHeightR = DirectionR.Size() / 2.f;
	FVector CapsuleOriginL = StartL + (EndL - StartL) / 2.f;
	FVector CapsuleOriginR = StartR + (EndR - StartR) / 2.f;
	FColor DrawColor = bSuccessL || bSuccessR ? FColor::Green : FColor::Red;
	FQuat QuatRotationL = FQuat::FindBetweenNormals(FVector::UpVector, DirectionL.GetSafeNormal());
	FQuat QuatRotationR = FQuat::FindBetweenNormals(FVector::UpVector, DirectionR.GetSafeNormal());

	DrawDebugCapsule(
		GetWorld(),
		CapsuleOriginL,
		CapsuleHalfHeightL,
		AttackRadius,
		QuatRotationL,
		DrawColor,
		false,
		1.f,
		0
	);

	DrawDebugCapsule(
		GetWorld(),
		CapsuleOriginR,
		CapsuleHalfHeightR,
		AttackRadius,
		QuatRotationR,
		DrawColor,
		false,
		1.f,
		0
	);

#endif
}

void AJK1Assassin::GetAndStoreMaterials()
{
	// 캐릭터의 Mesh Component 가져오기
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent)
	{
		// Material 개수 가져오기
		int32 MaterialCount = MeshComponent->GetNumMaterials();

		// 배열 초기화
		StoredMaterials.Empty();

		// Material들을 배열에 저장하기
		for (int32 Index = 0; Index < MaterialCount; ++Index)
		{
			UMaterialInterface* Material = MeshComponent->GetMaterial(Index);
			if (Material)
			{
				StoredMaterials.Add(Material);
				UE_LOG(LogTemp, Log, TEXT("Material at index %d: %s"), Index, *Material->GetName());
			}
		}
	}
}

void AJK1Assassin::TimelineProgress(float Value)
{
	TimelineValue = Value; // TimelineValue 변수 업데이트
	UE_LOG(LogAssassin, Log, TEXT("Timeline Value: %f"), TimelineValue);
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(FName(TEXT("Opacity")), TimelineValue);
	}
}
