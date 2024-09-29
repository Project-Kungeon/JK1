// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Widget/JK1ItemWidget.h"
#include "JK1InventorySlotWidget.generated.h"

class USizeBox;
class UImage;

/**
 * 
 */
UCLASS()
class JK1_API UJK1InventorySlotWidget : public UJK1ItemWidget
{
	GENERATED_BODY()

public:
	UJK1InventorySlotWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Slot;
};
