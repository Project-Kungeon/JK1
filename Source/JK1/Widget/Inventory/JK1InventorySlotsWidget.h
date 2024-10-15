// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Widget/JK1ItemWidget.h"
#include "JK1InventorySlotsWidget.generated.h"

class UJK1InventorySlotWidget;
class UUniformGridPanel;
class UJK1InventoryEntryWidget;
class AJK1ItemInstance;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class JK1_API UJK1InventorySlotsWidget : public UJK1ItemWidget
{
	GENERATED_BODY()
	
public:
	UJK1InventorySlotsWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativeConstruct() override;

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDrop, UDragDropOperation* InOperation);
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

public:
	void OnInventoryEntryChanged(const FIntPoint& InItemSlotPos, TObjectPtr<AJK1ItemInstance> Item);

private:
	void FinishDrag();

protected:
	UPROPERTY()
	TSubclassOf<UJK1InventorySlotWidget> SlotWidgetClass;

	UPROPERTY()
	TArray<TObjectPtr<UJK1InventorySlotWidget>> SlotWidgets;

	UPROPERTY()
	TSubclassOf<UJK1InventoryEntryWidget> EntryWidgetClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel_Slots;

public:
	UPROPERTY()
	TArray<TObjectPtr<UJK1InventoryEntryWidget>> EntryWidgets;

private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel_Entries;

private:
	FIntPoint PrevDragOverSlotPos = FIntPoint(-1, -1);
	const int X_COUNT = 10;
	const int Y_COUNT = 5;
};
