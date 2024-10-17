// Copyright 2024 All Rights Reserved by J&K


#include "Widget/Inventory/JK1InventorySlotWidget.h"
#include "Components/SizeBox.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UJK1InventorySlotWidget::UJK1InventorySlotWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UJK1InventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox_Root->SetWidthOverride(50); 
	SizeBox_Root->SetHeightOverride(50);
}
