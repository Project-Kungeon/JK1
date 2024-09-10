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

AJK1Warrior::AJK1Warrior()
	: Super()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (nullptr != DefaultMesh.Object)
	{
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);
	}

	CreatureStat->SetOwner(true, FName("Warrior"));

	SkillCooldown = 5.0f;
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

	/*----- 다른 방안 알아보기 -----*/
	/*if (!DashVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (DashVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}*/
}

void AJK1Warrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJK1Warrior::Attack()
{
	Super::Attack();
}

void AJK1Warrior::OnBasicAttackHit(TArray<FHitResult> HitResults)
{
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
	//WarriorQ();
	UE_LOG(LogWarrior, Log, TEXT("This is %s"), *this->GetName());
}

void AJK1Warrior::SkillE(const FInputActionValue& value)
{
	Super::SkillE(value);
	WarriorE();
}

void AJK1Warrior::SkillR(const FInputActionValue& value)
{
	Super::SkillR(value);
	WarriorR();
}

void AJK1Warrior::SkillLShift(const FInputActionValue& value)
{
	Super::SkillLShift(value);
	WarriorLShift();
}

void AJK1Warrior::WarriorQ()
{
}

void AJK1Warrior::WarriorE()
{
	if (!bWeaponActive && !AnimInstance->Montage_IsPlaying(CurrentMontage))
	{
		
		CurrentMontage = SkillEMontage_Intro;
		AnimInstance->Montage_Play(SkillEMontage_Intro);
		{
			IsAttacking = false;
			SaveAttacking = false;
			CurrentCombo = 0;
		}
		/*----멀티플레이 환경에서 패링이 테스트 가능해질 때 까지 코드 남겨둘 것 ----*/
		FTimerHandle TimerHandle;
		FTimerHandle TimerHandle2;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AJK1Warrior::SetParryActiveTrue, 1.f, false);
		GetWorldTimerManager().SetTimer(TimerHandle2, this, &AJK1Warrior::SetParryActiveFalse, 1.5f, false);
	}
}

void AJK1Warrior::WarriorR()
{
	if (AnimInstance && AnimInstance->Montage_IsPlaying(CurrentMontage))
	{
		return;
	}
	else
	{
		/*--------------------
		SetTimer 델리게이트 사용해서 연속해서 사용되는 문제 해결
	    --------------------*/
		if (!bWeaponActive)
		{
			IsAttacking = false;
			SaveAttacking = false;
			CurrentCombo = 0;

			CurrentMontage = SkillRMontage;
			
			AsyncTask(ENamedThreads::GameThread, [this]() {
				this->PlayAnimMontage(SkillRMontage);
				this->PlayParticleSystem();
				this->StartROverTime();
				}
			);
		}
	}
}

void AJK1Warrior::WarriorLShift()
{
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
		ApplyDamageToTarget(HitResults, 1.f);


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

	UGameInstance* instance = GetGameInstance();
	AsyncTask(ENamedThreads::GameThread, [this, TimerHandle, Duration, instance]()
		{
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
			}
		}
		
	);
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
TArray<FOverlapResult> AJK1Warrior::CheckSkillRTrace()
{
	UE_LOG(LogTemp, Log, TEXT("CheckSkillRTrace Active"));
	FVector Location = GetActorLocation();
	TArray<FOverlapResult> HitResults;
	TArray<FOverlapResult> ValidHitResults;	// 중복 처리된 피격자 리스트(would be returned)
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
				// HitPawn->CreatureStat->HitDamage(1.0f);
				ValidHitResults.Add(HitResult);
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

	return ValidHitResults;
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
//
//void AJK1Warrior::ResetSkillLShift()
//{
//	bCanMove = true;
//	// Reset the dash velocity
//	DashVelocity = FVector::ZeroVector;
//
//	// Clear the timer
//	GetWorldTimerManager().ClearTimer(DashTimerHandle);
//}


