// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1Item.h"
#include "Creature/PC/JK1PlayerCharacter.h"

UJK1Item::UJK1Item()
{
}

UJK1Item::UJK1Item(TObjectPtr<AJK1PlayerCharacter> player, message::ItemInfo& itemInfo)
	: _Owner(player), _count(0)
{
	_ItemInfo->CopyFrom(itemInfo);
}

UJK1Item::~UJK1Item()
{
	delete _ItemInfo;
	_ItemInfo = NULL;
}

bool UJK1Item::UseItem()
{
	_count--;
	return true;
}
