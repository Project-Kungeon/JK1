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
	//Timeline ����
	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("<MyTimeline"));
	
	//FloatCurve
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveRef(TEXT("/Game/Blueprints/Creature/PC/Assassin/CloakCurve.CloakCurve"));
	if (CurveRef.Succeeded())
	{
		FloatCurve = CurveRef.Object;
	}
	//Character Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKallari/Characters/Heroes/Kallari/Skins/Rogue/Meshes/Kallari_Rogue.Kallari_Rogue'"));
	if (DefaultMesh.Succeeded())
	{
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);
	}
	//Melee Success Particle Impact
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitEffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonKallari/FX/Particles/Kallari/Abilities/Primary/FX/P_Kallari_Melee_SucessfulImpact.P_Kallari_Melee_SucessfulImpact'"));
	if (HitEffectRef.Object)
	{
		HitEffect = HitEffectRef.Object;
	}
	//Cloaking Material Interface
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CloakMaterialRef(TEXT("/Script/Engine.Material'/Game/Blueprints/Creature/PC/Assassin/TPS_Material_Translucnet.TPS_Material_Translucnet'"));
	if (CloakMaterialRef.Succeeded())
	{
		CloakMaterial = CloakMaterialRef.Object;
	}
	CreatureStat->SetOwner(true, FName("Assassin"));
	SpawnLocation = FVector(-10.f, 0.f, 50.f); // ĳ���� ���� ��ġ
	ThrowDirection = FVector(1.f, 0.f, 0.f); // ������ ������
	ThrowForce = 1000.f; // ������ ��

	// Skill Q �� Ÿ��
	SkillQCoolDownTime = 3.0f;
	//Timeline ���� �ʱ�ȭ.
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

		// Timeline ��� ����
		MyTimeline->SetLooping(false);
		MyTimeline->SetIgnoreTimeDilation(true);
	}
	GetAndStoreMaterials();
}

void AJK1Assassin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyTimeline)
		MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance)
		if(AnimInstance->Montage_IsPlaying(SkillRMontage))
			CheckCharacterMovement();
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

	float ForwardValue = value.Get<float>();
	float RightValue = value.Get<float>();

	UE_LOG(LogAssassin, Log, TEXT("%f %f"), ForwardValue, RightValue);

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
	FVector End = Start + (GetActorForwardVector() * 1000.f); // 1000 ���� �ձ��� Ʈ���̽�

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
		OnAssassinQ_Hit(HitResult);
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
				//TODO : ������ ����
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
	
	Super::SkillR(Value);
	UE_LOG(LogAssassin, Log, TEXT("This is %s"), *this->GetName());
	//TODO: Forward & RightValue�� 0���� �ƴ϶�� �ٷ� ��Ÿ�� ����.,

	PlayAnimMontage(SkillRMontage, 1.5f);

}

void AJK1Assassin::CheckCharacterMovement()
{
	FVector Velocity = GetVelocity();
	float Speed = Velocity.Size();

	if (Speed != 0.0f)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
			AnimInstance->Montage_Stop(0.2f, SkillRMontage);
	}
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
		//���� ����
		IsCloakingProcess = true;
		ChangeStatusEffect(true, 3);
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
		//���� ����
		IsCloakingProcess = true;
		ChangeStatusEffect(false, 3);
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

void AJK1Assassin::OnAttackHit(TArray<FHitResult> hits)
{
}

void AJK1Assassin::OnAssassinQ_Hit(FHitResult hit)
{
}

void AJK1Assassin::CheckWeaponTrace()
{
	if (!bBAActive)
		return;

	
	float AttackRadius = 20.f;
	if (CurrentCombo == 3)
	{
		AttackRadius = 30.f;
	}
	bool IsRight = (CurrentCombo != 2) ? true : false;
	FVector StartL = GetMesh()->GetSocketLocation(FName(TEXT("sword_base_l")));
	FVector EndL = GetMesh()->GetSocketLocation(FName(TEXT("sword_tip_l")));

	FVector StartR = GetMesh()->GetSocketLocation(FName(TEXT("sword_base_r")));
	FVector EndR = GetMesh()->GetSocketLocation(FName(TEXT("sword_tip_r")));

	FVector ExtendL = EndL - StartL;
	FVector ExtendR = EndR - StartR;
	//const float AttackRadius = 20.f;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);


	bool bSuccess = GetWorld()->SweepMultiByChannel(
		HitResults,
		IsRight ? StartR : StartL,
		IsRight ? EndR : EndL,
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		FCollisionShape::MakeCapsule(IsRight ? ExtendR : ExtendL),
		Params
	);

	if (bSuccess)
		ApplyDamageToTarget(HitResults, 1.0f);
	
#if ENABLE_DRAW_DEBUG
	FVector DirectionL = EndL - StartL;
	FVector DirectionR = EndR - StartR;
	float CapsuleHalfHeightL = DirectionL.Size() / 2.f;
	float CapsuleHalfHeightR = DirectionR.Size() / 2.f;
	FVector CapsuleOriginL = StartL + (EndL - StartL) / 2.f;
	FVector CapsuleOriginR = StartR + (EndR - StartR) / 2.f;
	FColor DrawColor = bSuccess ? FColor::Green : FColor::Red;
	FQuat QuatRotationL = FQuat::FindBetweenNormals(FVector::UpVector, DirectionL.GetSafeNormal());
	FQuat QuatRotationR = FQuat::FindBetweenNormals(FVector::UpVector, DirectionR.GetSafeNormal());


	DrawDebugCapsule(
		GetWorld(),
		IsRight ? CapsuleOriginR : CapsuleOriginL,
		IsRight ? CapsuleHalfHeightR : CapsuleHalfHeightL,
		AttackRadius,
		IsRight ? QuatRotationR : QuatRotationL,
		DrawColor,
		false,
		1.f,
		0
	);

#endif
	if (!ValidHitResults.IsEmpty()) OnAttackHit(ValidHitResults);

}

void AJK1Assassin::GetAndStoreMaterials()
{
	// ĳ������ Mesh Component ��������
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent)
	{
		// Material ���� ��������
		int32 MaterialCount = MeshComponent->GetNumMaterials();

		// �迭 �ʱ�ȭ
		StoredMaterials.Empty();

		// Material���� �迭�� �����ϱ�
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
	TimelineValue = Value; // TimelineValue ���� ������Ʈ
	UE_LOG(LogAssassin, Log, TEXT("Timeline Value: %f"), TimelineValue);
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(FName(TEXT("Opacity")), TimelineValue);
	}
}
