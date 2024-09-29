// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "JK1Define.h"
#include "UObject/NoExportTypes.h"
#include "JK1ItemInstance.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class JK1_API UJK1ItemInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UJK1ItemInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init(int32 InItemID);


public:
	UPROPERTY()
	int32 ItemID = 0;

	UPROPERTY()
	EItemRarity ItemRarity = EItemRarity::Junk;
};
