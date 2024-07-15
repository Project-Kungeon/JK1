// Copyright 2024 All Rights Reserved by J&K


#include "JK1CreatureStatComponent.h"
#include "../JK1GameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UJK1CreatureStatComponent::UJK1CreatureStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UJK1CreatureStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UJK1CreatureStatComponent::InitializeComponent()
{
	// initialize stat
	

	BasicStatData = nullptr;
	IsPlayer = true;
	CurrentHP = 0;
	CurrentStat[0] = 0;
	CurrentStat[1] = 0;
}

// Called every frame
void UJK1CreatureStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJK1CreatureStatComponent::HitDamage(float NewDamage, AController* instigator)
{
	check(BasicStatData != nullptr);
	//
	//if (AJK1PlayerController* DamageActorController = Cast<AJK1PlayerController>(instigator))
	//	DamageInstigator.AddUnique(DamageActorController);

	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage / CurrentStat[1], 0.f, BasicStatData->MaxHP));
}

void UJK1CreatureStatComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	//OnHPChanged.Broadcast();

	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.f;
		//OnHPIsZero.Broadcast();

		// TEMP CODE
		//if (!DamageInstigator.IsEmpty())
		//{
		//	for (AJ1PlayerController* instigator : DamageInstigator)
		//	{
		//		if (auto character = Cast<ACharacterBase>(instigator->GetPawn()))
		//		{
		//			character->CharacterStat->PlusExp(CurrentStatData->DropExp);
		//		}
		//	}
		//}
	}
}
