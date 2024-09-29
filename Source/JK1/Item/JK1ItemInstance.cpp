// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1ItemInstance.h"

UJK1ItemInstance::UJK1ItemInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UJK1ItemInstance::Init(int32 InItemID)
{
	if (InItemID <= 0)
		return;

	ItemID = InItemID;

	ItemRarity = EItemRarity::Common;
}
