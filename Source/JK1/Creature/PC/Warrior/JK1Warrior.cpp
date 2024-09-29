// Copyright 2024 All Rights Reserved by J&K


#include "JK1Warrior.h"
#include "../../JK1CreatureStatComponent.h"
#include "GameFramework/PlayerController.h"
#include "JK1/Physics/JK1Collision.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

AJK1Warrior::AJK1Warrior()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (nullptr != DefaultMesh.Object)
	{
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);
	}

	CreatureStat->SetOwner(true, FName("Warrior"));

	{
		SetQ(WarriorQCT);
		SetE(WarriorECT);
		SetR(WarriorRCT);
		SetLS(WarriorLSCT);
	}
}

void AJK1Warrior::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(CurrentMontage);
}

void AJK1Warrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bParryActive)
	{
		CheckDamagedInParry();
	}
}

void AJK1Warrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJK1Warrior::Attack()
{
	Super::Attack();
}

void AJK1Warrior::ComboActionBegin()
{
	Super::ComboActionBegin();
}

void AJK1Warrior::DoCombo()
{
	Super::DoCombo();

	switch (CurrentCombo)
	{
	case 0:
		PlayAnimMontage(ComboActionMontage1, 1.4f);
		break;
	case 1:
		PlayAnimMontage(ComboActionMontage2, 1.4f);
		break;
	case 2:
		PlayAnimMontage(ComboActionMontage3, 1.4f);
		break;
	}
}

void AJK1Warrior::ComboActionEnd()
{
	Super::ComboActionEnd();
}

void AJK1Warrior::SkillQ(const FInputActionValue& value)
{
	Super::SkillQ(value);
	UE_LOG(LogWarrior, Log, TEXT("This is %s"), *this->GetName());
	bQActive = true;
	SetQ(0.f);
	//GetWorldTimerManager().SetTimer(Qhandler, this, &AJK1Warrior::StartQTimer, 0.1f, true);
	StartQTimer();

}

void AJK1Warrior::SkillE(const FInputActionValue& value)
{
	Super::SkillE(value);

	if (!bWeaponActive && !AnimInstance->Montage_IsPlaying(CurrentMontage))
	{
		
		CurrentMontage = SkillEMontage_Intro;
		AnimInstance->Montage_Play(SkillEMontage_Intro);
		{
			IsAttacking = false;
			SaveAttacking = false;
			CurrentCombo = 0;
		}
		bParryCount = true;
		SetE(0.f);
		GetWorldTimerManager().SetTimer(Ehandler, this, &AJK1Warrior::StartETimer, 0.1f, true);
	}
}

void AJK1Warrior::SkillR(const FInputActionValue& value)
{
	Super::SkillR(value);
	if (AnimInstance && AnimInstance->Montage_IsPlaying(CurrentMontage))
	{
		return;
	}
	else 
	{
		if (!bWeaponActive)
		{
			IsAttacking = false;
			SaveAttacking = false;
			CurrentCombo = 0;

			CurrentMontage = SkillRMontage;
			PlayAnimMontage(SkillRMontage);
			PlayParticleSystem();
			StartROverTime();
			//Cooltime

			SetR(0.f);
			StartRTimer();
		}
	}
	
}

void AJK1Warrior::SkillLShift(const FInputActionValue& value)
{
	Super::SkillLShift(value);
	if (AnimInstance && AnimInstance->Montage_IsPlaying(CurrentMontage))
		return;
	else
	{
		//bCanMove = false;
		//1000.f 1.f
		//FVector ForwardDash = GetActorForwardVector() * (DashDistance / DashDuration);
		//DashVelocity = ForwardDash;

		CurrentMontage = SkillLShiftMontage;
		PlayAnimMontage(SkillLShiftMontage);

		FVector ForwardDirection = GetActorForwardVector();

		LaunchCharacter(ForwardDirection * ForwardStrength + FVector(0, 0, JumpStrength), true, true);

		SetLS(0.f);
		StartLSTimer();
	} 
}

void AJK1Warrior::CheckDamagedInParry()
{
	UE_LOG(LogWarrior, Log, TEXT("this is CheckDamagedInParry"));

	if (!bParryActive)
		return;

	if (/*Server TODO: Check Damaged?*/true && bParryCount)
	{
		//TODO : Get Zero Damage
		//TODO shield attack
		ParryCount <= 4 ? ParryCount++ : ParryCount = 5;

		UE_LOG(LogWarrior, Log, TEXT("%d"), ParryCount);
		bParryCount = false;

		PlayAnimMontage(SkillEMontage_HitReact, 1.f);
	}
}

void AJK1Warrior::CheckBATrace()
{
	Super::CheckBATrace();

	if (!bBAActive)
		return;

	UE_LOG(LogTemp, Log, TEXT("This is Check WeaponTrace"));
	FVector Start = GetMesh()->GetSocketLocation(FName(TEXT("FX_Sword_Bottom")));
	FVector End = GetMesh()->GetSocketLocation(FName(TEXT("FX_Sword_Top")));
	FVector Extend = End - Start;
	const float AttackRadius = 20.f;

	TArray<FHitResult> HitResults;
	//FHitResult HitResult;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	/*  sweep / multi / ByChannel */

	bool bSuccess = GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		FCollisionShape::MakeCapsule(Extend),
		Params
	);

	if (bSuccess)
	{
		if (bQActive)
		{
			ApplyDamageToTarget(HitResults, 1.f + 0.2f * ParryCount);
			ParryCount = 0;
			bQActive = false;
		}
		else
			ApplyDamageToTarget(HitResults, 1.f);
	}


#if ENABLE_DRAW_DEBUG
	FVector Direction = End - Start;
	float CapsuleHalfHeight = Direction.Size() / 2.f;
	FVector CapsuleOrigin = Start + (End - Start) / 2.f;
	FColor DrawColor = bSuccess ? FColor::Green : FColor::Red;
	FQuat QuatRotation = FQuat::FindBetweenNormals(FVector::UpVector, Direction.GetSafeNormal());

	DrawDebugCapsule(
		GetWorld(),
		CapsuleOrigin,
		CapsuleHalfHeight,
		AttackRadius,
		QuatRotation,
		DrawColor,
		false,
		1.f,
		0
	);

#endif
}

void AJK1Warrior::PlayParticleSystem()
{
	FTimerHandle TimerHandle;
	//timer
	const float Duration = 5.f;

	ParticleSystemComponent = UGameplayStatics::SpawnEmitterAttached(
		SkillREffect,
		GetMesh(),
		TEXT("NONE"),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		EAttachLocation::KeepRelativeOffset,
		false
	);

	if (ParticleSystemComponent)
	{
		// 파티클 시스템 재생
		ParticleSystemComponent->Activate(true);

		// 일정 시간 후에 파티클 시스템 제거를 위한 타이머 설정
		//이건 파티클 제거를 위한 목적이니 남겨둠.
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			this,
			&AJK1Warrior::StopParticleSystem,
			Duration,
			false
		);
	}
}

void AJK1Warrior::DealDamageOverTime()
{
	// 남은 시간이 있다면 데미지를 적용
	if (RemainingDamageTime > 0)
	{
		CheckSkillRTrace();
		RemainingDamageTime -= DamageInterval;

		// 남은 시간이 0 이하가 되면 타이머 중지
		if (RemainingDamageTime <= 0)
		{
			GetWorldTimerManager().ClearTimer(DamageTimerHandle);
			ResetSkillCooldown();
		}
	}
}

void AJK1Warrior::StartROverTime()
{
	// 총 데미지 지속 시간 초기화
	RemainingDamageTime = DamageDuration;

	CheckSkillRTrace();

	GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &AJK1Warrior::DealDamageOverTime, DamageInterval, true);
}

//return type Tarray변경
void AJK1Warrior::CheckSkillRTrace()
{
	UE_LOG(LogTemp, Log, TEXT("CheckSkillRTrace Active"));
	FVector Location = GetActorLocation();
	TArray<FOverlapResult> HitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	bool bSuccess = GetWorld()->OverlapMultiByChannel(
		HitResults,
		GetActorLocation(),
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		FCollisionShape::MakeSphere(400.0f),
		Params
	);

	if (bSuccess)
	{
		for (const FOverlapResult& HitResult : HitResults)
		{
			AActor* OverlappingActor = HitResult.GetActor();
			//Take Damage
			if (AJK1CreatureBase* HitPawn = Cast<AJK1CreatureBase>(OverlappingActor))
			{
				//HitPawn->CreatureStat->HitDamage(1.0f);
			}
			FVector OverlapLocation = OverlappingActor->GetActorLocation();
			float SphereRadius = 50.0f;
			FColor SphereColor = FColor::Green;
			float LifeTime = 5.0f;

			DrawDebugSphere(
				GetWorld(),
				OverlapLocation,
				SphereRadius,
				32,
				SphereColor,
				false,
				LifeTime
			);
		}
	}
	HitResults.Empty();
}

void AJK1Warrior::StopParticleSystem()
{
	if (ParticleSystemComponent)
	{
		ParticleSystemComponent->Deactivate();
		ParticleSystemComponent->DestroyComponent();
	}
}

void AJK1Warrior::ResetSkillCooldown()
{
	{
		//이걸 안해주면 콤보 제어 변수가 이상하게 변경됨.
		IsAttacking = false;
		SaveAttacking = false;
		CurrentCombo = 0;
	}
}

/*
* 버프의 지속시간이 있는 스킬의 경우 
* 스킬 쿨타임 조절, 버프 지속시간 조절용 2개의 timer 사용
* 아닌경우 스킬 쿨타임 조절 Handler만 사용.
*/
void AJK1Warrior::StartQTimer()
{
	Super::StartQTimer();
	//Skill CoolTime Timer
	GetWorldTimerManager().SetTimer(Qhandler, [this]()
		{
			if (GetQ() < 1.f)
			{
				SetQ(GetQ() + 0.1f / WarriorQCT);

				if (GetQ() >= 1.f)
				{
					SetQ(1.f);
					GetWorldTimerManager().ClearTimer(Qhandler);
				}
			}

		}
	, 0.1f, true);

	//Buff CoolTime Timer
	QLeftTime = 1.f;

	GetWorldTimerManager().SetTimer(QBuffHandler, [this]()
		{
			QLeftTime -= 0.1f / QBuffTime;

			if (QLeftTime <= 0)
			{
				QLeftTime = 0.f;
				GetWorldTimerManager().ClearTimer(QBuffHandler);
			}

		}
	, 0.1f, true);
}
void AJK1Warrior::StartETimer()
{
	Super::StartETimer();
	GetWorldTimerManager().SetTimer(Ehandler, [this]()
		{
			if (GetE() < 1.f)
			{
				SetE(GetE() + 0.1f / WarriorECT);

				if (GetE() >= 1.f)
				{
					SetE(1.f);
					GetWorldTimerManager().ClearTimer(Ehandler);
				}
			}
		}
	, 0.1f, true);
	
}

void AJK1Warrior::StartRTimer()
{
	Super::StartRTimer();
	GetWorldTimerManager().SetTimer(Rhandler, [this]()
		{
			if (GetR() < 1.f)
			{
				SetR(GetR() + 0.1f / WarriorRCT);

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
			}

		}
	, 0.1f, true);

}
void AJK1Warrior::StartLSTimer()
{
	Super::StartLSTimer();
	GetWorldTimerManager().SetTimer(LShandler, [this]()
		{
			if (GetLS() < 1.f)
			{
				SetLS(GetLS() + 0.1f / WarriorLSCT);

				if (GetLS() >= 1.f)
				{
					SetLS(1.f);
					GetWorldTimerManager().ClearTimer(LShandler);
				}
			}

		}
	, 0.1f, true);
}

