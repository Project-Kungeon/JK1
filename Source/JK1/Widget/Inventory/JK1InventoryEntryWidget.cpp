// Copyright 2024 All Rights Reserved by J&K


#include "Widget/Inventory/JK1InventoryEntryWidget.h"
#include "Widget/Inventory/JK1InventorySlotsWidget.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Item/JK1Item.h"
#include "Item/JK1Item.h"
#include "Item/JK1InventorySubsystem.h"
#include "JK1Define.h"
#include "JK1InventorySlotsWidget.h"
#include "JK1InventoryEntryWidget.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Widget/Item/Drag/JK1DragDropOperation.h"
#include "Widget/Item/Drag/JK1ItemDragWidget.h"


UJK1InventoryEntryWidget::UJK1InventoryEntryWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UJK1ItemDragWidget> FindDragWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Item/WBP_ItemDrag.WBP_ItemDrag_C'"));
	if (FindDragWidgetClass.Succeeded())
	{
		DragWidgetClass = FindDragWidgetClass.Class;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_JK1Item(TEXT("/Script/Engine.DataTable'/Game/Data/DT_ItemData.DT_ItemData'"));
	check(DT_JK1Item.Succeeded());
	JK1ItemTable = DT_JK1Item.Object;
	check(JK1ItemTable->GetRowMap().Num() > 0);
}

void UJK1InventoryEntryWidget::Init(UJK1InventorySlotsWidget* InSlotWidget, UJK1Item* InItemInstance)
{
	SlotsWidget = InSlotWidget;
	ItemInstance = InItemInstance;
	ItemCount = ItemInstance->GetItemCount();
	
	ItemClass = JK1ItemTable->FindRow<FJK1ItemData>(FName(FString::FromInt(ItemInstance->GetItemID())), TEXT(""))->ItemClass;
	Text_Count->SetText((ItemCount >= 2) ? FText::AsNumber(ItemCount) : FText::GetEmpty());
	Image_Icon->SetBrushFromTexture(GetItemImage(InItemInstance->GetItemTable()), true);

	// TODO : 이곳에서 이미지 결정.


}

void UJK1InventoryEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Count->SetText(FText::GetEmpty());
}

void UJK1InventoryEntryWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	// 마우스를 갖다대면 뜨는 설명이 잘보이게
	Image_Hover->SetRenderOpacity(1.f);
}

void UJK1InventoryEntryWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	Image_Hover->SetRenderOpacity(0.f);
}

FReply UJK1InventoryEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	const FIntPoint UnitInventorySlotSize = FIntPoint(50, 50);

	FVector2D MouseWidgetPos = SlotsWidget->GetCachedGeometry().AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	FVector2D ItemWidgetPos = SlotsWidget->GetCachedGeometry().AbsoluteToLocal(InGeometry.LocalToAbsolute(UnitInventorySlotSize / 2.f));
	FIntPoint ItemSlotPos = FIntPoint(ItemWidgetPos.X / UnitInventorySlotSize.X, ItemWidgetPos.Y / UnitInventorySlotSize.Y);


	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		auto temp = Cast<AJK1PlayerCharacter>(GetOwningPlayer()->GetPawn());
		if (temp != nullptr)
		{

			ItemInstance->UseItem();
			//ItemInstance->SetItemCount(-1);
			ItemCount--;
			if (ItemInstance->GetItemCount() == 0)
			{
				// inventory에서 해당 item 제거
				UJK1InventorySubsystem* Inventory = Cast<UJK1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UJK1InventorySubsystem::StaticClass()));
				Inventory->RemoveItem(ItemInstance->GetItemID());
				SlotsWidget->OnInventoryEntryChanged(ItemSlotPos, nullptr);
			}
			else
				Text_Count->SetText((ItemCount >= 2) ? FText::AsNumber(ItemCount) : FText::GetEmpty());
			
		}
	}

	CachedFromSlotPos = ItemSlotPos;
	CachedDeltaWidgetPos = MouseWidgetPos - ItemWidgetPos;

	return reply;
}


void UJK1InventoryEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UJK1ItemDragWidget* DragWidget = CreateWidget<UJK1ItemDragWidget>(GetOwningPlayer(), DragWidgetClass);
	FVector2D EntityWidgetSize = FVector2D(1 * 50, 1 * 50);
	DragWidget->Init(EntityWidgetSize, GetItemImage(ItemInstance->GetItemID()), ItemCount);
	
	UJK1DragDropOperation* DragDrop = NewObject<UJK1DragDropOperation>();
	DragDrop->DefaultDragVisual = DragWidget;
	DragDrop->Pivot = EDragPivot::MouseDown;
	DragDrop->FromItemSlotPos = CachedFromSlotPos;
	DragDrop->ItemInstance = ItemInstance;
	DragDrop->DeltaWidgetPos = CachedDeltaWidgetPos;

	OutOperation = DragDrop;
}

void UJK1InventoryEntryWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	RefreshWidgetOpacity(true);
}

void UJK1InventoryEntryWidget::RefreshWidgetOpacity(bool bClearlyVisible)
{
	SetRenderOpacity(bClearlyVisible ? 1.f : 0.5f);
}

void UJK1InventoryEntryWidget::RefreshItemCount(int32 NewItemCount)
{
	ItemCount = NewItemCount;
	Text_Count->SetText((ItemCount >= 2) ? FText::AsNumber(ItemCount) : FText::GetEmpty());
}

UTexture2D* UJK1InventoryEntryWidget::GetItemImage(int ItemId)
{
	return JK1ItemTable->FindRow<FJK1ItemData>(FName(FString::FromInt(ItemId)), TEXT(""))->Thumnail;
}
