// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1ItemInstance.h"
#include "Item/JK1InventorySubsystem.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/JK1CreatureStatComponent.h"

AJK1ItemInstance::AJK1ItemInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AJK1ItemInstance::BeginPlay()
{
	Super::BeginPlay();
}

void AJK1ItemInstance::Init(int32 InItemID)
{
	if (InItemID <= 0)
		return;

	ItemID = InItemID;
	ItemCount = 1;
	ItemRarity = EItemRarity::Common;
}

void AJK1ItemInstance::UseItem(AJK1PlayerCharacter* OwningPlayer)
{
	if (type != EItemType::Consumable)
		return;
}

void AJK1ItemInstance::InterActive()
{
	UJK1InventorySubsystem* Inventory = Cast<UJK1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UJK1InventorySubsystem::StaticClass()));
	if (Inventory)
	{
		Inventory->AddNewItem(ItemID);
	}
}
