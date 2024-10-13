// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Item/JK1ConsumeableItem.h"
#include "NJK1ConsumeableItem.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API ANJK1ConsumeableItem : public AJK1ConsumeableItem
{
	GENERATED_BODY()
	
public:
	ANJK1ConsumeableItem();

public:
	virtual void	UseItem(AJK1PlayerCharacter* OwningPlayer) override;
	virtual void	InterActive() override;
};
