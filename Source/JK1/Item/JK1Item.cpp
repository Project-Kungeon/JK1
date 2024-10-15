// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1Item.h"
#include "Creature/PC/JK1PlayerCharacter.h"

UJK1Item::UJK1Item(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	_ItemInfo = new message::ItemInfo();
}

UJK1Item::~UJK1Item()
{
	delete _ItemInfo;
	_ItemInfo = NULL;
}

void UJK1Item::Init(TObjectPtr<AJK1PlayerCharacter> player, const message::InventorySlot& Slot)
{
	_Owner = player;
	_count = Slot.cnt();;
	_ItemInfo->CopyFrom(Slot.iteminfo());

}

bool UJK1Item::UseItem()
{
	_count--;
	return true;
}
