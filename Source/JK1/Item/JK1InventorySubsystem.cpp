// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1InventorySubsystem.h"
#include "Item/JK1ItemInstance.h"

void UJK1InventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UJK1InventorySubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UJK1InventorySubsystem::AddNewItem(int ItemId)
{
	TObjectPtr<UJK1ItemInstance> Item = NewObject<UJK1ItemInstance>();
	Item->Init(ItemId);
	Items.Add(Item);
}
