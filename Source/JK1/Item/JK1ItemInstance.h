// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JK1Define.h"
#include "JK1/Interface/InteractiveObjectInterface.h"
#include "JK1ItemInstance.generated.h"

class AJK1PlayerCharacter;

/**
 * 
 */
UCLASS(BlueprintType)
class JK1_API AJK1ItemInstance : public AActor, public IInteractiveObjectInterface
{
	GENERATED_BODY()
	
public:
	AJK1ItemInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void	BeginPlay() override;

	/*
	*	Member Function
	*/
public:
	void			Init(int32 InItemID, EItemType type, EItemRarity Rarity);

public:
	virtual void	UseItem(AJK1PlayerCharacter* OwningPlayer);
	virtual void	InterActive() override;

	int32			GetItemID()				{ return ItemID; }
	int32			GetItemCount()			{ return ItemCount; }
	void			SetItemCount(int value) { ItemCount += value; }

	/*
	*	Member Variable
	*/
protected:
	UPROPERTY()
	int32			ItemID = 1;
	int32			ItemCount = 0;

	UPROPERTY()
	EItemType		Itemtype = EItemType::Consumable;

	UPROPERTY()
	EItemRarity		ItemRarity = EItemRarity::Junk;
};
