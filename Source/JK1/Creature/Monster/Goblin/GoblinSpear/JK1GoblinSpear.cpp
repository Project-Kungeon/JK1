// Copyright 2023. Jerry. All rights reserved.


#include "JK1GoblinSpear.h"
#include "Components/CapsuleComponent.h"
#include "Creature/JK1CreatureStatComponent.h"

AJK1GoblinSpear::AJK1GoblinSpear()
{
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Enemies/Goblin/Spear/SKM_Spear.SKM_Spear'"));
	//if (WeaponMesh.Succeeded())
	//	Weapon->SetSkeletalMesh(WeaponMesh.Object);
}

void AJK1GoblinSpear::BeginPlay()
{
	Super::BeginPlay();

	CreatureStat->SetOwner(false, "GoblinSlingSpear");
}

void AJK1GoblinSpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJK1GoblinSpear::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
