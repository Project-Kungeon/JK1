// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "JK1/Interface/ItemInterface.h"
#include "JK1Item.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API UJK1Item : public UItemInterface
{
	GENERATED_BODY()

public:
	UJK1Item();
	UJK1Item(TObjectPtr<AJK1PlayerCharacter> player, message::ItemInfo& itemInfo);
	~UJK1Item();

public:
	virtual bool UseItem();

	int32 GetItemID() const { return (_ItemInfo) ? _ItemInfo->item_id() : -1; }
	int32 GetItemCount() const { return _count; }

	message::ItemType GetItemType() const { return _ItemInfo->item_type(); }
	message::ItemTable GetItemTable() const { return _ItemInfo->item_table(); }


protected:
	message::ItemInfo* _ItemInfo;
	int32 _count;

	TWeakObjectPtr<AJK1PlayerCharacter> _Owner;
};
