// Copyright 2024 All Rights Reserved by J&K


#include "Creature/Monster/Boss/JK1Rampage.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Components/CapsuleComponent.h"

AJK1Rampage::AJK1Rampage()
{
	// Default Settings
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Skins/Tier2/Elemental/Meshes/Rampage_Elemental.Rampage_Elemental'"));
	if (DefaultMesh.Succeeded())
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);

	Super::GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -75.f), FRotator(0, -90.f, 0));
	Super::GetCapsuleComponent()->SetCapsuleHalfHeight(75.f);

	// AI
	AIControllerClass = AJK1RampageController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	CreatureStat->SetOwner(false, FName("Rampage"));
}

void AJK1Rampage::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogMonster, Log, TEXT("Rampage : Beginplay Call"));
}

void AJK1Rampage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJK1Rampage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
