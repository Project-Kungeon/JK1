// Copyright 2023. Jerry. All rights reserved.


#include "JK1GoblinBase.h"
#include "Components/CapsuleComponent.h"
#include "Creature/JK1CreatureStatComponent.h"

AJK1GoblinBase::AJK1GoblinBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CreatureStat->SetOwner(false, "GoblinBase");

	// Weapon Setting
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Default Settings
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Skins/Tier2/Elemental/Meshes/Rampage_Elemental.Rampage_Elemental'"));
	if (DefaultMesh.Succeeded())
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);

	Super::GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -75.f), FRotator(0, -90.f, 0));
	Super::GetCapsuleComponent()->SetCapsuleHalfHeight(75.f);
}

void AJK1GoblinBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogMonster, Log, TEXT("GoblinBase: Beginplay Call"));
}

void AJK1GoblinBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJK1GoblinBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
