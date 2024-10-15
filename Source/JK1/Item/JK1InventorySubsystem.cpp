// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1InventorySubsystem.h"
#include "Item/JK1ItemInstance.h"
#include "Item/JK1ConsumeableItem.h"

UJK1InventorySubsystem::UJK1InventorySubsystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_JK1Item(TEXT("/Script/Engine.DataTable'/Game/Data/DT_ItemData.DT_ItemData'"));
	check(DT_JK1Item.Succeeded());
	JK1ItemTable = DT_JK1Item.Object;
	check(JK1ItemTable->GetRowMap().Num() > 0);
}

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
	FJK1ItemData* ItemRow = GetItemTableRow(ItemId);

	Item->Init(ItemId, ItemRow->Type, ItemRow->ItemRarity);
	if (Items.Contains(ItemId))
	{
		TObjectPtr<AJK1ItemInstance> temp = *(Items.Find(ItemId));
		temp->SetItemCount(1);	
	}
	else
		Items.Add(ItemId, Item);
}

FJK1ItemData* UJK1InventorySubsystem::GetItemTableRow(int ItemId)
{
	return JK1ItemTable->FindRow<FJK1ItemData>(FName(FString::FromInt(ItemId)), TEXT(""));
}