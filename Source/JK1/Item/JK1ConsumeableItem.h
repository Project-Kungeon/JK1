// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Item/JK1Item.h"
#include "JK1ConsumeableItem.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API UJK1ConsumeableItem : public UJK1Item
{
	GENERATED_BODY()
public:
	UJK1ConsumeableItem(const FObjectInitializer& ObjectInitializer);

public:
	virtual bool UseItem() override;
};
