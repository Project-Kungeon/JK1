// Copyright 2024 All Rights Reserved by J&K


#include "JK1Warrior.h"
#include "../../JK1CreatureStatComponent.h"
#include "JK1/Physics/JK1Collision.h"

#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/DamageEvents.h"
#include "Particles/ParticleSystemComponent.h"

AJK1Warrior::AJK1Warrior()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (nullptr != DefaultMesh.Object)
	{
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);
	}

	CreatureStat->SetOwner(true, FName("Warrior"));
}

void AJK1Warrior::BeginPlay()
{
	Super::BeginPlay();
}

void AJK1Warrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bWeaponActive)
		CheckWeaponTrace();
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
		CurrentCombo = 1;
		PlayAnimMontage(ComboActionMontage1, 1.4f);
		break;
	case 1:
		CurrentCombo = 2;
		PlayAnimMontage(ComboActionMontage2, 1.4f);
		break;
	case 2:
		CurrentCombo = 3;
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
}

void AJK1Warrior::SkillE(const FInputActionValue& value)
{
	Super::SkillE(value);
}

void AJK1Warrior::SkillR(const FInputActionValue& value)
{
	Super::SkillR(value);
	PlayAnimMontage(SkillRMontage, 1.4f);
	PlayParticleSystem();
	CheckSkillRTrace();
}

void AJK1Warrior::SkillLShift(const FInputActionValue& value)
{
	Super::SkillLShift(value);
}

void AJK1Warrior::CheckWeaponTrace()
{
	if (!bWeaponActive)
		return;

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
		FDamageEvent DamageEvent;

		for (FHitResult& HitResult : HitResults)
		{
			AActor* Actor = HitResult.GetActor();
			if (Actor == nullptr)
				continue;

			if (WeaponAttackTargets.Contains(Actor) == false)
			{
				WeaponAttackTargets.Add(Actor);

				if (AJK1CreatureBase* HitPawn = Cast<AJK1CreatureBase>(Actor))
				{
					// Server Code need
					HitPawn->CreatureStat->HitDamage(1.0f);
					UE_LOG(LogWarrior, Log, TEXT("Hit target: %s"), *Actor->GetName());
				}

			}
		}

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
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			this,
			&AJK1Warrior::StopParticleSystem,
			Duration,
			false
		);
	}
}

void AJK1Warrior::CheckSkillRTrace()
{
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
}

void AJK1Warrior::StopParticleSystem()
{
	if (ParticleSystemComponent)
	{
		ParticleSystemComponent->Deactivate();
		ParticleSystemComponent->DestroyComponent();
	}
}