// Copyright 2024 All Rights Reserved by J&K


#include "JK1Archor.h"
#include "JK1/Physics/JK1Collision.h"
#include "../../JK1CreatureStatComponent.h"
#include "JK1/Creature/PC/Archor/JK1Arrow.h"
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
#include "Containers/Array.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"

AJK1Archor::AJK1Archor()
{
	//Path of Arrow Actor Blueprint Class
	//해당 부분 C++ Class 로 전환
	ArrowBP = TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Creature/PC/Archor/BP_JK1Arrow.BP_JK1Arrow'");

	//Montage 상하체 미 분리때문에 발생하는 현상
	//GetCharacterMovement()->bOrientRotationToMovement = false;
	//bUseControllerRotationYaw = true;

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
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SkillReffectRef(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_SparrowBuff.P_SparrowBuff'"));
	if (SkillReffectRef.Succeeded())
	{
		SkillReffect = SkillReffectRef.Object;
	}

	//Archor Jump Range 조절.
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AddForce(FVector(100.f, 0.f, 0.f));
	GetCharacterMovement()->AirControl = 1.f;

	//Camera Offset 
	CameraBoom->SocketOffset = FVector(0.f, 120.f, 75.f);
	
	CreatureStat->SetOwner(true, FName("Archor"));

	{
		SetQ(ArchorQCT);
		SetE(ArchorECT);
		SetR(ArchorRCT);
		SetLS(ArchorLSCT);
	}
}

void AJK1Archor::BeginPlay()
{
	Super::BeginPlay();
	AnimInstance = GetMesh()->GetAnimInstance();
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

void AJK1Archor::OnBasicAttackHit(TArray<FHitResult> HitResults)
{
}

void AJK1Archor::Shoot(FVector StartLoc, FVector EndLoc)
{
	ObjectToSpawn = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *ArrowBP.ToString()));

	FHitResult HitResult;	// 히트 대상
	FVector EndLocation;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	ImpactPoint = StartLoc + EndLoc;

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLoc,
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
			TArray<FHitResult> HitResults;
			HitResults.Add(HitResult);
			OnBasicAttackHit(HitResults);
		}
		if (IsLShift)
		{
			CurrentTime = MaxTime;
			GetWorldTimerManager().SetTimer(ArrowHandler, [this, StartLoc, EndLoc]()
				{
					this->SpawnArrowCheck(StartLoc, EndLoc);
				}, 0.1f, true);
			//TODO : 데미지 5
		}
		else
		{
			SpawnArrow(StartLoc, EndLoc);
			//TODO : 데미지 1
		}
	}
	

#if ENABLE_DRAW_DEBUG
	FVector Direction = ImpactPoint - CrosshairWorldLocation;
	FColor DrawColor = bSuccess ? FColor::Green : FColor::Red;
	FQuat QuatRotation = FQuat::FindBetweenNormals(FVector::UpVector, Direction.GetSafeNormal());

	DrawDebugLine(
		GetWorld(),
		StartLoc,
		ImpactPoint,
		DrawColor,
		false,
		3.f,
		0,
		3.f
	);
#endif
}

void AJK1Archor::ShootQ(FVector StartLoc, FVector EndLoc)
{
	PlayAnimMontage(SkillQMonatge_Recovery);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	ObjectToSpawn = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *ArrowBP.ToString()));

	FHitResult HitResult;	// 히트 대상
	FVector EndLocation;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	ImpactPoint = StartLoc + EndLoc;

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLoc,
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
			OnArchorQ_Hit(HitResult);
		}
		SpawnArrow(StartLoc, EndLoc);
	}
#if ENABLE_DRAW_DEBUG
	FVector Direction = ImpactPoint - CrosshairWorldLocation;
	FColor DrawColor = bSuccess ? FColor::Green : FColor::Red;
	FQuat QuatRotation = FQuat::FindBetweenNormals(FVector::UpVector, Direction.GetSafeNormal());

	DrawDebugLine(
		GetWorld(),
		StartLoc,
		ImpactPoint,
		DrawColor,
		false,
		3.f,
		0,
		3.f
	);
#endif
}

void AJK1Archor::SpawnArrow(FVector StartLoc, FVector EndLoc)
{
	AJK1Arrow* Arrow = nullptr;
	//LShift 상태면 랜덤한 스타팅 포인트에서 화살 발사
	if (IsLShift)
	{
		float Radius = 50.0f; // 원하는 반지름 크기
		FVector RandomDirection = UKismetMathLibrary::RandomUnitVector();
		FVector Offset = RandomDirection * Radius;
		ArrowStartLocation = StartLoc + Offset;
		ImpactPoint = StartLoc + EndLoc;
		ArrowSpawnRotation = (ImpactPoint - ArrowStartLocation).Rotation();

		Arrow = GetWorld()->SpawnActor<AJK1Arrow>(ObjectToSpawn->GeneratedClass,
			ArrowStartLocation, ArrowSpawnRotation, SpawnParams);

		// 디버그용으로 원의 가장자리에 있는 화살의 시작 위치 표시
		DrawDebugSphere(
			GetWorld(),
			ArrowStartLocation,
			10.0f,
			12,
			FColor::Blue,
			false,
			3.0f
		);
	}
	else //아니라면 CameraForward Vector방향으로 발사
	{
		ArrowSpawnRotation = (ImpactPoint - StartLoc).Rotation();

		Arrow = GetWorld()->SpawnActor<AJK1Arrow>(ObjectToSpawn->GeneratedClass,
			StartLoc, ArrowSpawnRotation, SpawnParams);
	}
	
	//Arrow가 Channel 제외한 다른 액터와 판정 안되게 하는 구문
	if (Arrow)
	{
		UPrimitiveComponent* CollisionComponent = Cast<UPrimitiveComponent>(Arrow->GetComponentByClass(UPrimitiveComponent::StaticClass()));
		if (CollisionComponent)
		{
			CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			CollisionComponent->SetCollisionObjectType(CCHANNEL_JK1ACTION);

			// 모든 채널을 무시하고, 특정 채널에 대해서만 반응
			CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
			CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		}
	}
}

void AJK1Archor::SpawnArrowCheck(FVector StartLoc, FVector EndLoc)
{
	if (CurrentTime > 0)
	{
		CurrentTime--;
		SpawnArrow(StartLoc, EndLoc);
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
	FVector ShootPoint = GetMesh()->GetSocketLocation(FName(TEXT("BowEmitterSocket")));

	Super::DoCombo();
	switch (CurrentCombo)
	{
	case 0:
		CurrentCombo = 1;
		if (GetWorld())
		{
			APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
			FVector ArrowStartLoc = GetStartArrowLoc(CameraManager);
			FVector ArrowEndLoc = GetEndArrowLoc(CameraManager);
			ArchorAttack(ArrowStartLoc, ArrowEndLoc);
		}
		
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

	ArchorQ_Charging();
}

void AJK1Archor::SkillE(const FInputActionValue& value)
{
	Super::SkillE(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());
	
	ArchorE(CalculateDamageLocation());
}

void AJK1Archor::SkillR(const FInputActionValue& value)
{
	Super::SkillR(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());
	ArchorR();
}

void AJK1Archor::SkillLShift(const FInputActionValue& value)
{
	Super::SkillLShift(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());

	ArchorLS();

}

void AJK1Archor::ArchorAttack(FVector StartPoint, FVector EndPoint)
{
	AsyncTask(ENamedThreads::GameThread, [this, StartPoint, EndPoint]() {

		PlayAnimMontage(ComboActionMontage, ComboActionMontagePlayRate);
		Shoot(StartPoint, EndPoint);
		});

	
}

void AJK1Archor::ArchorQ_Charging()
{

	AsyncTask(ENamedThreads::GameThread, [this]() {
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
			PlayAnimMontage(SkillQMonatge_Charge, SkillRChargePlayRate);
			FTimerHandle ChargeHandler;
			GetWorldTimerManager().SetTimer(ChargeHandler, this, &AJK1Archor::ShootNRecovery, SkillQMontagePlayRate, false);
			SetQ(0);
			GetWorldTimerManager().SetTimer(Qhandler, this, &AJK1Archor::StartQTimer, 0.1f, true);
		}
		});

	
}

void AJK1Archor::ArchorQ_Shot(FVector StartPoint, FVector EndPoint)
{
	ShootQ(StartPoint, EndPoint);
}

void AJK1Archor::ArchorE(FVector Point)
{
	//89.56f
	//SkillELocation = FVector(CalculateDamageLocation().X, CalculateDamageLocation().Y, 0.f);

	AsyncTask(ENamedThreads::GameThread, [this, Point]() {
		SkillELocation = FVector(Point.X, Point.Y, 0.f);

		PlayAnimMontage(SkillEMontage);
		StartDamage();
		PlayParticleSystem();
		SetE(0);
		GetWorldTimerManager().SetTimer(Ehandler, this, &AJK1Archor::StartETimer, 0.1f, true);
		});

	
}

void AJK1Archor::ArchorR()
{
	{
		ComboActionMontagePlayRate = 2.0f;
		SkillQMontagePlayRate = 0.2f;
		SkillRChargePlayRate = 5.0f;
		SetR(0);
		GetWorldTimerManager().SetTimer(Rhandler, this, &AJK1Archor::StartRTimer, 0.1f, true);
	}
}

void AJK1Archor::ArchorLS()
{
	IsLShift = true;
	GetWorldTimerManager().SetTimer(LShiftTimerHandler, this, &AJK1Archor::BIsLShift, 5.0f, false);
	SetLS(0);
	GetWorldTimerManager().SetTimer(LShandler, this, &AJK1Archor::StartLSTimer, 0.1f, true);
	//FTimerHandle LShiftTimerHandler;

	//GetWorldTimerManager().SetTimer(LShiftTimerHandler, this, &AJK1Archor::BIsLShift, 5.0f, false);
}

FVector AJK1Archor::GetStartArrowLoc(APlayerCameraManager* CameraManager)
{
	return CameraManager->GetCameraLocation();
}

FVector AJK1Archor::GetEndArrowLoc(APlayerCameraManager* CameraManager)
{
	FVector EndLoc = CameraManager->GetActorForwardVector();
	EndLoc.X *= 15000;
	EndLoc.Y *= 15000;
	EndLoc.Z *= 15000;

	return EndLoc;
}

void AJK1Archor::OnArrowHit(FHitResult hit)
{

}

void AJK1Archor::OnArchorQ_Hit(FHitResult hit)
{
}

void AJK1Archor::OnArchorE_Hit(TArray<FHitResult> hits)
{
}

void AJK1Archor::ShootNRecovery()
{
	if (GetWorld())
	{
		APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
		ShootQ(GetStartArrowLoc(CameraManager), GetEndArrowLoc(CameraManager));
	}
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
	CheckSkillETrace();

	GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &AJK1Archor::DealDamage, DamageInterval, true);
}

void AJK1Archor::StopDamage()
{
	GetWorldTimerManager().ClearTimer(DamageTimerHandle);

	if (SkillEDamageEffectComponent)
	{
		SkillEDamageEffectComponent->Deactivate();
	}
}

void AJK1Archor::CheckSkillETrace()
{
	AsyncTask(ENamedThreads::GameThread, [this]() {
		// 타격 위치 계산
		FVector DamageLocation = SkillELocation;

		// 구체로 범위를 지정하고 그 안의 모든 액터를 가져옵니다.
		TArray<FHitResult> OverlappingActors;
		// 타격 위치 계산

		DrawDebugSphere(
			GetWorld(),
			DamageLocation,
			DamageRadius,
			12,
			FColor::Red,
			false,
			5.0f
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
			OnArchorE_Hit(OverlappingActors);
			for (FHitResult& result : OverlappingActors)
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
		});
}

void AJK1Archor::PlayParticleSystem()
{
	FTimerHandle TimerHandle;

	const float SkillEDuration = 5.f;
	
	SkillEDamageEffectComponent = UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		SkillEeffect,
		SkillELocation,
		FollowCamera->GetComponentRotation(),
		false
	);

	if (SkillEDamageEffectComponent)
	{
		// 파티클 시스템 재생
		SkillEDamageEffectComponent->Activate(true);

		// 일정 시간 후에 파티클 시스템 제거를 위한 타이머 설정
		//이건 파티클 제거를 위한 목적이니 남겨둠.
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			this,
			&AJK1Archor::StopParticleSystem,
			SkillEDuration,
			false
		);
	}
}

void AJK1Archor::StopParticleSystem()
{
	if (SkillEDamageEffectComponent)
	{
		SkillEDamageEffectComponent->Deactivate();
		SkillEDamageEffectComponent->DestroyComponent();
	}
}

void AJK1Archor::StartQTimer()
{
	Super::StartQTimer();
	GetWorldTimerManager().SetTimer(Qhandler, [this]()
		{
			if (GetQ() < 1.f)
			{
				SetQ(GetQ() + 0.1f / ArchorQCT);

				if (GetQ() >= 1.f)
				{
					SetQ(1.f);
					GetWorldTimerManager().ClearTimer(Qhandler);
				}
			}

		}
	, 0.1f, true);
}

void AJK1Archor::StartETimer()
{
	Super::StartETimer();
	GetWorldTimerManager().SetTimer(Ehandler, [this]()
		{
			if (GetE() < 1.f)
			{
				SetE(GetE() + 0.1f / ArchorECT);

				if (GetE() >= 1.f)
				{
					SetE(1.0f);
					GetWorldTimerManager().ClearTimer(Ehandler);
				}
			}
		}
	, 0.1f, true);
}

void AJK1Archor::StartRTimer()
{
	Super::StartRTimer();
	GetWorldTimerManager().SetTimer(Rhandler, [this]()
		{
			if (GetR() < 1.f)
			{
				SetR(GetR() + 0.1f / ArchorRCT);

				if (GetR() >= 1.f)
				{
					SetR(1.f);
					GetWorldTimerManager().ClearTimer(Rhandler);
				}
			}

		}
	, 0.1f, true);

	//Buff CoolTime Timer
	RLeftTime = 1.f;

	GetWorldTimerManager().SetTimer(RBuffHandler, [this]()
		{
			RLeftTime -= 0.1f / RBuffTime;

			if (RLeftTime <= 0)
			{
				RLeftTime = 0.f;
				GetWorldTimerManager().ClearTimer(RBuffHandler);
				EndSkillR();
			}

		}
	, 0.1f, true);
}

void AJK1Archor::StartLSTimer()
{
	Super::StartLSTimer();
	GetWorldTimerManager().SetTimer(LShandler, [this]()
		{
			if (GetLS() < 1.f)
			{
				SetLS(GetLS() + 0.1f / ArchorLSCT);

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

FVector AJK1Archor::CalculateDamageLocation()
{
	return GetActorLocation() + GetActorForwardVector() * DamageDistance;
}
