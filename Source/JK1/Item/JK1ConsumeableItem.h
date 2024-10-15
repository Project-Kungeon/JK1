// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Item/JK1ItemInstance.h"
#include "JK1ConsumeableItem.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1ConsumeableItem : public AJK1ItemInstance
{
	GENERATED_BODY()
	
public:
	AJK1ConsumeableItem();

public:
	virtual void UseItem(AJK1PlayerCharacter* OwningPlayer);
};
