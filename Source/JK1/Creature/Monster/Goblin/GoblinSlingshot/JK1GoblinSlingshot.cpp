// Copyright 2023. Jerry. All rights reserved.

#include "JK1GoblinSlingshot.h"
#include "Components/CapsuleComponent.h"
#include "Creature/JK1CreatureStatComponent.h"

AJK1GoblinSlingshot::AJK1GoblinSlingshot()
{
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Assets/Enemies/Goblin/Slingshot/Centered/SKM_Slingshot.SKM_Slingshot'"));
	//if (WeaponMesh.Succeeded())
	//	Weapon->SetSkeletalMesh(WeaponMesh.Object);
}

void AJK1GoblinSlingshot::BeginPlay()
{
	Super::BeginPlay();

	CreatureStat->SetOwner(false, "GoblinSlingShot");
}

void AJK1GoblinSlingshot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJK1GoblinSlingshot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
