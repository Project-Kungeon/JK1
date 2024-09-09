// Fill out your copyright notice in the Description page of Project Settings.


#include "JK1CreatureBase.h"
#include "JK1CreatureStatComponent.h"
#include "JK1LogChannels.h"
#include "Controller/Player/JK1PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <BrainComponent.h>

// Sets default values
AJK1CreatureBase::AJK1CreatureBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterBase"));
	CreatureStat = CreateDefaultSubobject<UJK1CreatureStatComponent>(TEXT("CreatureStat"));
	
	// 0000|0000
	statusEffect = 0;
	bBAActive = false;
}

// Called when the game starts or when spawned
void AJK1CreatureBase::BeginPlay()
{
	Super::BeginPlay();

	CreatureStat->OnHPIsZero.AddDynamic(this, &AJK1CreatureBase::Death);
}

// Called every frame
void AJK1CreatureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJK1CreatureBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AJK1CreatureBase::TakeDamage(float damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCursor)
{
	const float ActualDamage = Super::TakeDamage(damage, DamageEvent, EventInstigator, DamageCursor);

	//CreatureStat->HitDamage(ActualDamage, EventInstigator);

	return ActualDamage;
}

void AJK1CreatureBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!IsPlayerControlled())
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);  // 회전 속도

		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

void AJK1CreatureBase::CheckBATrace()
{
}

void AJK1CreatureBase::ChangeStatusEffect(bool On, int status)
{
	if (On)
		statusEffect |= (1 << status);
	else
		statusEffect &= ~(1 << status);

	ApplyStatusEffect();
}

void AJK1CreatureBase::ApplyStatusEffect()
{
	if (statusEffect & (1 << 0))
	{
		CreatureStat->SetImmunity(true);
		UE_LOG(LogCreature, Log, TEXT("면역"));
	}
	else
	{
		if (statusEffect & (1 << 1))
		{
			GetCharacterMovement()->MaxWalkSpeed /= 2;
			UE_LOG(LogCreature, Log, TEXT("이감"));
		}
		else if (statusEffect & (1 << 2))
		{
			Cast<AJK1PlayerController>(GetController())->RemoveInputSystem();
			UE_LOG(LogCreature, Log, TEXT("기절"));
		}
		else if (statusEffect & (1 << 3))
		{
			UE_LOG(LogCreature, Log, TEXT("은신"));
		}
	}
}

void AJK1CreatureBase::ApplyDamageToTarget(TArray<FHitResult> HitResults, float damage)
{
	for (FHitResult& HitResult : HitResults)
	{
		AActor* Actor = HitResult.GetActor();
		if (Actor == nullptr)
			continue;

		if (BasicAttackTargets.Contains(Actor) == false)
		{
			BasicAttackTargets.Add(Actor);

			if (AJK1CreatureBase* HitPawn = Cast<AJK1CreatureBase>(Actor))
			{
				// Server Code need
				if (HitPawn->CreatureStat->HitDamage(damage, Controller))
				{
					UE_LOG(LogSystem, Log, TEXT("Hit target: %s"), *Actor->GetName());
				}
				else
					UE_LOG(LogSystem, Log, TEXT("%s is immunity"), *Actor->GetName());
			}
		}
	}
}

void AJK1CreatureBase::Death()
{
	StopAnimMontage();
}

