// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "JK1DragDropOperation.generated.h"

class UJK1Item;

/**
 * 
 */
UCLASS()
class JK1_API UJK1DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UJK1DragDropOperation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	FIntPoint FromItemSlotPos = FIntPoint::ZeroValue;

	UPROPERTY()
	TObjectPtr<UJK1Item> ItemInstance;
	
	FVector2D DeltaWidgetPos = FVector2D::ZeroVector;
};
