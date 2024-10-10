// Copyright 2024 All Rights Reserved by J&K


#include "Widget/Inventory/JK1InventorySlotsWidget.h"
#include "Widget/Inventory/JK1InventorySlotWidget.h"
#include "Widget/Inventory/JK1InventoryEntryWidget.h"
#include "Widget/Item/Drag/JK1DragDropOperation.h"
#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Item/JK1InventorySubsystem.h"
#include "Item/JK1ItemInstance.h"
#include "JK1Define.h"


UJK1InventorySlotsWidget::UJK1InventorySlotsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UJK1InventorySlotWidget> FindSlotWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Item/Inventory/WBP_InventorySlot.WBP_InventorySlot_C'"));
	if (FindSlotWidgetClass.Succeeded())
	{
		SlotWidgetClass = FindSlotWidgetClass.Class;
	}

	ConstructorHelpers::FClassFinder<UJK1InventoryEntryWidget> FindEntryWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Item/Inventory/WBP_InventoryEntry.WBP_InventoryEntry_C'"));
	if (FindEntryWidgetClass.Succeeded())
	{
		EntryWidgetClass = FindEntryWidgetClass.Class;
	}
}

void UJK1InventorySlotsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SlotWidgets.SetNum(X_COUNT * Y_COUNT);

	for (int32 y = 0; y < Y_COUNT; y++)
	{
		for (int32 x = 0; x < X_COUNT; x++)
		{
			int32 index = y * X_COUNT + x;

			UJK1InventorySlotWidget* SlotWidget = CreateWidget<UJK1InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
			SlotWidgets[index] = SlotWidget;
			GridPanel_Slots->AddChildToUniformGrid(SlotWidget, y, x);
		}
	}

	EntryWidgets.SetNum(X_COUNT * Y_COUNT);

	UJK1InventorySubsystem* Inventory = Cast<UJK1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UJK1InventorySubsystem::StaticClass()));
	
	// inventory item 목록 가져오기
	int index = 0;
	const TMultiMap<int, TObjectPtr<AJK1ItemInstance>>& Items = Inventory->GetItems();
	for (auto it : Items)
	{
		const TObjectPtr<AJK1ItemInstance>& Item = it.Value;
		FIntPoint ItemSlotPos = FIntPoint(index % X_COUNT, index / X_COUNT);
		OnInventoryEntryChanged(ItemSlotPos, Item);
		index++;
	}
}

void UJK1InventorySlotsWidget::OnInventoryEntryChanged(const FIntPoint& InItemSlotPos, TObjectPtr<AJK1ItemInstance> Item)
{
	int32 SlotIndex = InItemSlotPos.Y * X_COUNT + InItemSlotPos.X;

	if (UJK1InventoryEntryWidget* EntryWidget = EntryWidgets[SlotIndex])
	{
		if (Item == nullptr)
		{
			CanvasPanel_Entries->RemoveChild(EntryWidget);
			EntryWidgets[SlotIndex] = nullptr;
		}
	}
	else
	{
		EntryWidget = CreateWidget<UJK1InventoryEntryWidget>(GetOwningPlayer(), EntryWidgetClass);
		EntryWidgets[SlotIndex] = EntryWidget;
		

		UCanvasPanelSlot* CanvasPanelSlot = CanvasPanel_Entries->AddChildToCanvas(EntryWidget);
		CanvasPanelSlot->SetAutoSize(true);
		CanvasPanelSlot->SetPosition(FVector2D(InItemSlotPos.X * 50, InItemSlotPos.Y * 50));

		// TODO
		EntryWidget->Init(this, Item);
	}
}

bool UJK1InventorySlotsWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDrop, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDrop, InOperation);

	UJK1DragDropOperation* DragDrop = Cast<UJK1DragDropOperation>(InOperation);
	check(DragDrop);

	FVector2D MouseWidgetPos = InGeometry.AbsoluteToLocal(InDragDrop.GetScreenSpacePosition());
	FVector2D ToWidgetPos = MouseWidgetPos - DragDrop->DeltaWidgetPos;
	FIntPoint ToSlotPos = FIntPoint(ToWidgetPos.X / Item::UnitInventorySlotSize.X, ToWidgetPos.Y / Item::UnitInventorySlotSize.Y);

	if (PrevDragOverSlotPos == ToSlotPos)
		return true;

	PrevDragOverSlotPos = ToSlotPos;

	// TODO

	return false;
}

void UJK1InventorySlotsWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	FinishDrag();
}

bool UJK1InventorySlotsWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	FinishDrag();

	UJK1DragDropOperation* DragDrop = Cast<UJK1DragDropOperation>(InOperation);
	check(DragDrop);


	FVector2D MouseWidgetPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FVector2D ToWidgetPos = MouseWidgetPos - DragDrop->DeltaWidgetPos;
	FIntPoint ToItemSlotPos = FIntPoint(ToWidgetPos.X / Item::UnitInventorySlotSize.X, ToWidgetPos.Y / Item::UnitInventorySlotSize.Y);

	// TODO 아이템 위치 교체
	if (DragDrop->FromItemSlotPos != ToItemSlotPos)
	{
		OnInventoryEntryChanged(DragDrop->FromItemSlotPos, nullptr);
		OnInventoryEntryChanged(ToItemSlotPos, DragDrop->ItemInstance);
	}

	return false;
}

void UJK1InventorySlotsWidget::FinishDrag()
{
	PrevDragOverSlotPos = FIntPoint(-1, -1);
}
