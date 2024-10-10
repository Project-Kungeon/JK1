// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "JK1InventorySubsystem.generated.h"

class AJK1ItemInstance;

/**
 * 
 */
UCLASS()
class JK1_API UJK1InventorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	//TEMP
	void AddNewItem(int ItemId);
	void RemoveItem(int ItemId) { Items.Remove(ItemId); }

	TMultiMap<int, TObjectPtr<AJK1ItemInstance>>& GetItems() { return Items; }

protected:
	TMultiMap<int, TObjectPtr<AJK1ItemInstance>> Items;
};
