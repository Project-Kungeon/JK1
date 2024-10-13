// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Engine/DataTable.h"
#include "JK1Define.h"
#include "JK1InventorySubsystem.generated.h"

class UJK1Item;

USTRUCT(BlueprintType)
struct FJK1ItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemRarity ItemRarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UJK1Item> ItemClass;
};

/**
 * 
 */
UCLASS()
class JK1_API UJK1InventorySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UJK1InventorySubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	//TEMP
	void AddNewItem(int ItemId);
	void RemoveItem(int ItemId) { Items.Remove(ItemId); }

	FJK1ItemData* GetItemTableRow(int ItemId);

	TMultiMap<int, TObjectPtr<UJK1Item>>& GetItems() { return Items; }

protected:
	TMultiMap<int, TObjectPtr<UJK1Item>> Items;

private:
	UPROPERTY()
	class UDataTable* JK1ItemTable;
};
