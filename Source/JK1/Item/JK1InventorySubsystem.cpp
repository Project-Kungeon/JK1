// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1InventorySubsystem.h"
#include "Item/JK1Item.h"
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

void UJK1InventorySubsystem::UpdateInventory(TObjectPtr<AJK1PlayerCharacter> my_player, const game::item::S_Item_OpenInventory& pkt)
{
	// 패킷 받고 업데이트
	Items.Reset();
	for (auto& slot : pkt.slots())
	{
		if (slot.iteminfo().item_id() == 0 || slot.cnt() == 0)
		{
			continue;
		}
		else
		{
			
			// 아이템 타입 구분 후 저장
			if (slot.iteminfo().item_type() == message::ItemType::Consumable)
			{
				TObjectPtr<UJK1ConsumeableItem> ConsumeableItem = NewObject<UJK1ConsumeableItem>();
				ConsumeableItem->Init(my_player, slot);
				Items.Add(slot.iteminfo().item_id(), ConsumeableItem);
			}
			else
			{
				TObjectPtr<UJK1Item> DefaultItem(NewObject<UJK1Item>());
				DefaultItem->Init(my_player, slot);
				Items.Add(slot.iteminfo().item_id(), DefaultItem);
			}
		}
	}


}

void UJK1InventorySubsystem::AddNewItem(int ItemId)
{
	//TObjectPtr<UJK1Item> Item = NewObject<UJK1Item>();
	//FJK1ItemData* ItemRow = GetItemTableRow(ItemId);

	//Item->Init(ItemId, ItemRow->Type, ItemRow->ItemRarity);
	//if (Items.Contains(ItemId))
	//{
	//	TObjectPtr<AJK1ItemInstance> temp = *(Items.Find(ItemId));
	//	temp->SetItemCount(1);	
	//}
	//else
	//	Items.Add(ItemId, Item);
}

FJK1ItemData* UJK1InventorySubsystem::GetItemTableRow(int ItemId)
{
	return JK1ItemTable->FindRow<FJK1ItemData>(FName(FString::FromInt(ItemId)), TEXT(""));
}