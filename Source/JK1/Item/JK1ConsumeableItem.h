// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Item/JK1Item.h"

/**
 * 
 */
class JK1_API AJK1ConsumeableItem : public UJK1Item
{
	
public:
	AJK1ConsumeableItem();
	AJK1ConsumeableItem(TObjectPtr<AJK1PlayerCharacter> player, message::ItemInfo& itemInfo);

public:
	virtual bool UseItem() override;
};
