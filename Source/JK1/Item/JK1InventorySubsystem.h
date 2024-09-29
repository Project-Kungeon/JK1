// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "JK1InventorySubsystem.generated.h"

class UJK1ItemInstance;

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
	void RemoveItem();

	const TArray<TObjectPtr<UJK1ItemInstance>>& GetItems() { return Items; }

protected:
	UPROPERTY()
	TArray<TObjectPtr<UJK1ItemInstance>> Items;
};
