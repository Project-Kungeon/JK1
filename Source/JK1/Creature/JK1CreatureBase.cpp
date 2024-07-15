// Fill out your copyright notice in the Description page of Project Settings.


#include "JK1CreatureBase.h"
#include "JK1CreatureStatComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AJK1CreatureBase::AJK1CreatureBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CharacterBase"));
	CreatureStat = CreateDefaultSubobject<UJK1CreatureStatComponent>(TEXT("CreatureStat"));

}

// Called when the game starts or when spawned
void AJK1CreatureBase::BeginPlay()
{
	Super::BeginPlay();
	
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
	//TODO
	return 0.0f;
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

