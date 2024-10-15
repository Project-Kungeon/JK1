// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JK1/Interface/ItemInterface.h"
#include "JK1Item.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API UJK1Item : public UObject
{
	GENERATED_BODY()

public:
	UJK1Item(const FObjectInitializer& ObjectInitializer);
	~UJK1Item();

	void Init(TObjectPtr<AJK1PlayerCharacter> player, const message::InventorySlot& itemInfo);

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
