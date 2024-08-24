// Copyright 2024 All Rights Reserved by J&K


#include "JK1Archor.h"
#include "JK1/Physics/JK1Collision.h"
#include "../../JK1CreatureStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"

AJK1Archor::AJK1Archor()
{
	//Path of Arrow Actor Blueprint Class
	//해당 부분 C++ Class 로 전환
	path = TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Creature/PC/Archor/BP_JK1Arrow.BP_JK1Arrow'");

	//Montage 상하체 미 분리때문에 발생하는 현상
	//GetCharacterMovement()->bOrientRotationToMovement = false;
	//bUseControllerRotationYaw = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_JK1.IMC_JK1'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'"));
	if (nullptr != DefaultMesh.Object)
	{
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> SkillEeffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/RainOfArrows/FX/P_RainofArrows.P_RainofArrows'"));
	if (SkillEeffectRef.Succeeded())
	{
		SkillEeffect = SkillEeffectRef.Object;
	}
	//이렇게 해야 애니메이션이 두번 동작 안함
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AddForce(FVector(100.f, 0.f, 0.f));
	GetCharacterMovement()->AirControl = 1.f;

	//Camera Offset 처리
	CameraBoom->SocketOffset = FVector(0.f, 120.f, 75.f);
	
	CreatureStat->SetOwner(true, FName("Archor"));
}

void AJK1Archor::BeginPlay()
{
	Super::BeginPlay();
}

void AJK1Archor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJK1Archor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJK1Archor::Attack()
{
	Super::Attack();
	
}

void AJK1Archor::Shoot()
{
	ObjectToSpawn = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *path.ToString()));

	//Skeletal mesh의 idle 상태에서 화살 촉이 있는 부분
	FHitResult HitResult;
	//Location Of Camera(Line Trace start)
	
	FVector EndLocation;
	FVector ImpactPoint;

	//TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	//Camera Info 가져오기.
	if (GetWorld())
	{
		APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
		if (CameraManager)
		{
			CrosshairWorldLocation = CameraManager->GetCameraLocation();
			//카메라의 전방 벡터 가져오기.
			EndLocation = CameraManager->GetActorForwardVector();
			//scaling forward vector by 15,000, 추적의 끝 부분, Multifly Vector Size 15000
			EndLocation.X *= 15000;
			EndLocation.Y *= 15000;
			EndLocation.Z *= 15000;
			//탐지하고자 하는 끝부분, Impact Target Point
			ImpactPoint = CrosshairWorldLocation + EndLocation;
		}
	}

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		CrosshairWorldLocation,
		ImpactPoint,
		CCHANNEL_JK1ACTION,
		Params
	);

	if (bSuccess)
	{
		if (HitResult.bBlockingHit)
		{
			ImpactPoint = HitResult.ImpactPoint;
			UE_LOG(LogArchor, Log, TEXT("%d, %d, %d"), ImpactPoint.X, ImpactPoint.Y, ImpactPoint.Z);
		}
		ArrowSpawnRotation = (ImpactPoint - CrosshairWorldLocation).Rotation();
		//화살 생성
		if (IsLShift)
		{
			CurrentTime = MaxTime;
			GetWorldTimerManager().SetTimer(ArrowHandler, this, &AJK1Archor::SpawnArrowCheck, 0.1f, true);
		}
		else 
		{
			SpawnArrow();
		}
	}

	
	UE_LOG(LogArchor, Log, TEXT("%d %d %d"), )

#if ENABLE_DRAW_DEBUG
	FVector Direction = ImpactPoint - CrosshairWorldLocation;
	FColor DrawColor = bSuccess ? FColor::Green : FColor::Red;
	FQuat QuatRotation = FQuat::FindBetweenNormals(FVector::UpVector, Direction.GetSafeNormal());

	DrawDebugLine(
		GetWorld(),
		CrosshairWorldLocation,
		ImpactPoint,
		DrawColor,
		false,
		3.f,
		0,
		3.f
	);

#endif
}

void AJK1Archor::SpawnArrow()
{
	GetWorld()->SpawnActor<AActor>(ObjectToSpawn->GeneratedClass,
		CrosshairWorldLocation, ArrowSpawnRotation, SpawnParams);
}

void AJK1Archor::SpawnArrowCheck()
{
	if (CurrentTime > 0)
	{
		CurrentTime--;
		SpawnArrow();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ArrowHandler);
	}
}

void AJK1Archor::ComboActionBegin()
{
	Super::ComboActionBegin();
}

void AJK1Archor::DoCombo()
{
	Super::DoCombo();
	switch (CurrentCombo)
	{
	case 0:
		CurrentCombo = 1;
		PlayAnimMontage(ComboActionMontage, ComboActionMontagePlayRate);
		Shoot();
		break;
	}
}

void AJK1Archor::ComboActionEnd()
{
	Super::ComboActionEnd();
}

void AJK1Archor::SkillQ(const FInputActionValue& value)
{
	Super::SkillQ(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		PlayAnimMontage(SkillQMonatge_Charge, SkillRChargePlayRate);
		FTimerHandle ChargeHandler;
		GetWorldTimerManager().SetTimer(ChargeHandler, this, &AJK1Archor::ShootNRecovery, SkillQMontagePlayRate, false);
	}
}

void AJK1Archor::SkillE(const FInputActionValue& value)
{
	Super::SkillE(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());

	SkillELocation = FVector(CalculateDamageLocation().X,CalculateDamageLocation().Y, 0.f);

	StartDamage();

	PlayParticleSystem();
}

void AJK1Archor::SkillR(const FInputActionValue& value)
{
	Super::SkillR(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());
	{
		ComboActionMontagePlayRate = 2.0f;
		SkillQMontagePlayRate = 0.2f;
		SkillRChargePlayRate = 5.0f;
	}
	//TODO: Timer로 Rate 변수 초기화
}

void AJK1Archor::SkillLShift(const FInputActionValue& value)
{
	Super::SkillLShift(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());
	IsLShift = true;

	FTimerHandle LShiftTimerHandler;

	GetWorldTimerManager().SetTimer(LShiftTimerHandler, this,&AJK1Archor::BIsLShift, 5.0f, false);

}

void AJK1Archor::ShootNRecovery()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	Shoot();
	PlayAnimMontage(SkillQMonatge_Recovery);
}

void AJK1Archor::EndSkillR()
{
	ComboActionMontagePlayRate = 1.0f;
	SkillQMontagePlayRate = 1.5f;
	SkillRChargePlayRate = 2.f;
}

void AJK1Archor::DealDamage()
{
	if (RemainingDamageTime > 0)
	{
		CheckSkillETrace();
		RemainingDamageTime -= DamageInterval;

		// 남은 시간이 0 이하가 되면 타이머 중지
		if (RemainingDamageTime <= 0)
		{
			GetWorldTimerManager().ClearTimer(DamageTimerHandle);
		}
	}
}

void AJK1Archor::StartDamage()
{
	// 0.2초 간격으로 DealDamage 함수를 호출하고, 5초 후에 멈춥니다.
	RemainingDamageTime = 5.0f;

	CheckSkillETrace();

	GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &AJK1Archor::DealDamage, DamageInterval, true);
}

void AJK1Archor::StopDamage()
{
	GetWorldTimerManager().ClearTimer(DamageTimerHandle);

	if (DamageEffectComponent)
	{
		DamageEffectComponent->Deactivate();
	}
}

void AJK1Archor::CheckSkillETrace()
{
	// 타격 위치 계산
	FVector DamageLocation = SkillELocation;
	UE_LOG(LogArchor, Log, TEXT("%f %f %f"), DamageLocation.X, DamageLocation.Y, DamageLocation.Z);

	// 구체로 범위를 지정하고 그 안의 모든 액터를 가져옵니다.
	TArray<FHitResult> OverlappingActors;
	// 타격 위치 계산

	DrawDebugSphere(
		GetWorld(),
		DamageLocation,         // 스피어의 위치
		DamageRadius,           // 스피어의 반지름
		12,                     // 스피어를 구성하는 선분의 수 (디테일 수준)
		FColor::Red,            // 스피어의 색상
		false,                  // 지속 시간 이후에 제거 (false: 자동 제거)
		5.0f                    // 스피어가 표시될 시간 (초)
	);
	// Sphere를 생성하여 일정 범위 안에 있는 액터를 찾습니다.
	FCollisionShape DamageSphere = FCollisionShape::MakeSphere(DamageRadius);
	bool bHasHit = GetWorld()->SweepMultiByChannel(
		OverlappingActors,
		DamageLocation,
		DamageLocation,
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		DamageSphere
	);

	if (bHasHit)
	{
		for (FHitResult result : OverlappingActors)
		{
			UE_LOG(LogArchor, Log, TEXT("%s"), *result.GetActor()->GetName());
			AActor* SweepActor = result.GetActor();
			FVector SweepLocation = SweepActor->GetActorLocation();
			float SphereRadius = 50.f;
			FColor SphereColor = FColor::Green;
			float LifeTime = 5.0f;

			DrawDebugSphere(
				GetWorld(),
				SweepLocation,
				SphereRadius,
				32,
				SphereColor,
				false,
				LifeTime
			);
		}
	}
}

void AJK1Archor::PlayParticleSystem()
{
	FTimerHandle TimerHandle;
	const float Duration = 5.f;

	DamageEffectComponent = UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		SkillEeffect,
		SkillELocation,
		FollowCamera->GetComponentRotation(),
		false
	);

	if (DamageEffectComponent)
	{
		// 파티클 시스템 재생
		DamageEffectComponent->Activate(true);

		// 일정 시간 후에 파티클 시스템 제거를 위한 타이머 설정
		//이건 파티클 제거를 위한 목적이니 남겨둠.
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			this,
			&AJK1Archor::StopParticleSystem,
			Duration,
			false
		);
	}
}

void AJK1Archor::StopParticleSystem()
{
	if (DamageEffectComponent)
	{
		DamageEffectComponent->Deactivate();
		DamageEffectComponent->DestroyComponent();
	}
}

FVector AJK1Archor::CalculateDamageLocation()
{
	return GetActorLocation() + GetActorForwardVector() * DamageDistance;
}
