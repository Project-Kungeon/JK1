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
#include "Blueprint/UserWidget.h"



AJK1Assassin::AJK1Assassin()
	: Super()
{
	//Timeline ����
	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("<MyTimeline"));
	
	//CloakCurve
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveRef(TEXT("/Game/Blueprints/Creature/PC/Assassin/CloakCurve.CloakCurve"));
	if (CurveRef.Succeeded())
	{
		CloakCurve = CurveRef.Object;
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
	SpawnLocation = FVector(-10.f, 0.f, 50.f); // 캐릭터 앞의 위치
	ThrowDirection = FVector(1.f, 0.f, 0.f); // 앞으로 던지기
	ThrowForce = 1000.f; // 던지기 힘

	//Timeline 변수 초기화.
	TimelineValue = 0.0f;

	{
		SetQ(AssassinQCT);
		SetR(AssassinRCT);
		SetLS(AssassinLSCT);
	}
		
}

void AJK1Assassin::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterial = UMaterialInstanceDynamic::Create(CloakMaterial, this);

	if (CloakCurve)
	{
		FOnTimelineFloat ProgressFunction{};
		ProgressFunction.BindUFunction(this, FName("TimelineProgress"));
		MyTimeline->AddInterpFloat(CloakCurve, ProgressFunction);

		// Timeline 재생 설정
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
			PlayAnimMontage(ComboActionMontage1, 1.f);
			break;
		case 1:
			PlayAnimMontage(ComboActionMontage2, 1.f);
			break;
		case 2:
			PlayAnimMontage(ComboActionMontage3, 1.f);
			break;
		}
	
	
}

void AJK1Assassin::ComboActionEnd()
{
	Super::ComboActionEnd();
}

void AJK1Assassin::OnBasicAttackHit(TArray<FHitResult> HitResults)
{
}

void AJK1Assassin::SkillQ(const FInputActionValue& value)
{
	Super::SkillQ(value);
	FVector SpawnPoint = GetActorLocation() + SpawnLocation;
	FRotator SpawnRotation = GetActorRotation();
	AssassinQ(SpawnPoint, SpawnRotation);
}

void AJK1Assassin::SpawnDagger(FVector SpawnPoint, FRotator SpawnRotation)
{
	if (DaggerActor)
	{
		
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
		OnAssassinQ_Hit(HitResult);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 3, 0, 3);
		UE_LOG(LogTemp, Warning, TEXT("Pawn Hit: %s"), *HitResult.GetActor()->GetName());
	}
	else 
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3, 0, 3);
	}
}

bool AJK1Assassin::IsBackAttack(AActor* Actor, FHitResult& HitResult)
{
	if (Actor)
	{
		FVector ForwardVector = GetActorForwardVector();
		FVector OtherForwardVector = Actor->GetActorForwardVector();

		if (FVector::DotProduct(ForwardVector, OtherForwardVector) > 0)
		{
			return true;
			//if (HitEffect)
			//{
			//	//TODO : 데미지 증가
			//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitLocation);
			//	
			//}		
		}
	} 
	return false;
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
	//TODO: Forward & RightValue가 0ㅇ이 아니라면 바로 몽타주 종료.,

	PlayAnimMontage(SkillRMontage, 1.5f);
	SetR(0.f);
	StartRTimer();

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
	if (IsCloaking)
	{
		AssassinLSOff();
	}
	else
	{
		AssassinLSOn();
	}
}

void AJK1Assassin::AssassinQ(FVector SpawnPoint, FRotator SpawnRotation)
{
	UE_LOG(LogAssassin, Log, TEXT("This is %s"), *this->GetName());

	//FVector SpawnPoint = GetActorLocation() + SpawnLocation;
	//FRotator SpawnRotation = GetActorRotation();


	AsyncTask(ENamedThreads::GameThread, [this, SpawnPoint, SpawnRotation]() {
		SpawnDagger(SpawnPoint, SpawnRotation);
		PlayAnimMontage(SkillQMontage, 1.5f);
		SkillQTrace();
		SetQ(0.f);
		GetWorldTimerManager().SetTimer(Qhandler, this, &AJK1Assassin::StartQTimer, 0.1f, true);
		});
	
}

// 백어택 이펙트용 호출
void AJK1Assassin::AssassinE(FVector HitLocation)
{
	if (HitEffect)
	{
		AsyncTask(ENamedThreads::GameThread, [this, HitLocation]() {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitLocation);
		});
			
	}
}

void AJK1Assassin::AssassinR()
{
	PlayAnimMontage(SkillRMontage, 1.5f);
}

void AJK1Assassin::AssassinLSOn()
{
	if (IsCloakingProcess)
	{
		UE_LOG(LogAssassin, Log, TEXT("InCloakingProcess"));
		return;
	}
	if (!IsCloaking)
	{
		// 은신 진입
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
		SetLS(0.f);
		GetWorldTimerManager().SetTimer(LShandler, this, &AJK1Assassin::StartLSTimer, 0.1f, true);
	}
}

void AJK1Assassin::AssassinLSOff()
{
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

void AJK1Assassin::OnAssassinQ_Hit(FHitResult hit)
{
}

void AJK1Assassin::CheckBATrace()
{
	if (!bBAActive)
		return;
	bool IsRight = (CurrentCombo % 2 == 0) ? true : false;

	FVector StartL = GetMesh()->GetSocketLocation(FName(TEXT("sword_base_l")));
	FVector EndL = GetMesh()->GetSocketLocation(FName(TEXT("sword_tip_l")));

	FVector StartR = GetMesh()->GetSocketLocation(FName(TEXT("sword_base_r")));
	FVector EndR = GetMesh()->GetSocketLocation(FName(TEXT("sword_tip_r")));

	FVector ExtendL = EndL - StartL;
	FVector ExtendR = EndR - StartR;
	const float AttackRadius = 20.f;

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
	{
		ApplyDamageToTarget(HitResults, 1.0f);
	}
		
	
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

void AJK1Assassin::StartQTimer()
{
	Super::StartQTimer();

	GetWorldTimerManager().SetTimer(Qhandler, [this]()
		{
			if (GetQ() < 1.f)
			{
				SetQ(GetQ() + 0.1f / AssassinQCT);

				if (GetQ() >= 1.f)
				{
					SetQ(1.f);
					GetWorldTimerManager().ClearTimer(Qhandler);
				}
			}

		}
	, 0.1f, true);
}

void AJK1Assassin::StartRTimer()
{
	Super::StartRTimer();

	GetWorldTimerManager().SetTimer(Rhandler, [this]()
		{
			if (GetR() < 1.f)
			{
				SetR(GetR() + 0.1f / AssassinRCT);

				if (GetR() >= 1.f)
				{
					SetR(1.f);
					GetWorldTimerManager().ClearTimer(Rhandler);
				}
			}

		}
	, 0.1f, true);
}

void AJK1Assassin::StartLSTimer()
{
	Super::StartLSTimer();

	GetWorldTimerManager().SetTimer(LShandler, [this]()
		{
			if (GetLS() < 1.f)
			{
				SetLS(GetLS() + 0.1f / AssassinLSCT);

				if (GetLS() >= 1.f)
				{
					SetLS(1.f);
					GetWorldTimerManager().ClearTimer(LShandler);
				}
			}
		}
	, 0.1f, true);

	//Buff CoolTime Timer
	LSLeftTime = 1.f;

	GetWorldTimerManager().SetTimer(LSBuffHandler, [this]()
		{
			LSLeftTime -= 0.1f / LSBuffTime;

			if (LSLeftTime <= 0)
			{
				LSLeftTime = 0.f;
				GetWorldTimerManager().ClearTimer(LSBuffHandler);
			}
		}
	, 0.1f, true);

}
