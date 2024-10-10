// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1InventorySubsystem.h"
#include "Item/JK1ItemInstance.h"
#include "Item/JK1ConsumeableItem.h"

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
	TObjectPtr<AJK1ConsumeableItem> Item = NewObject<AJK1ConsumeableItem>();
	Item->Init(ItemId);
	if (Items.Contains(ItemId))
	{
		TObjectPtr<AJK1ItemInstance> temp = *(Items.Find(ItemId));
		temp->SetItemCount(1);	
	}
	else
		Items.Add(ItemId, Item);
}