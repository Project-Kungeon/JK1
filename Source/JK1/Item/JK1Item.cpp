// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1Item.h"
#include "Item/JK1InventorySubsystem.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/JK1CreatureStatComponent.h"

// Sets default values
AJK1Item::AJK1Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AJK1Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJK1Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJK1Item::InterActive()
{
	UJK1InventorySubsystem* Inventory = Cast<UJK1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UJK1InventorySubsystem::StaticClass()));
	if (Inventory)
	{
		Inventory->AddNewItem(ItemID);
	}
}

void AJK1Item::UseItem(AJK1PlayerCharacter* OwningPlayer)
{
	if (type != EItemType::Consumable)
		return;
	else
	{
		if (ItemID == 1)
			OwningPlayer->CreatureStat->SetCurrentHP(OwningPlayer->CreatureStat->GetCurrentHP() + 50.f);
	}
}