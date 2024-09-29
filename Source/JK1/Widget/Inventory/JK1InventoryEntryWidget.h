// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Widget/JK1ItemWidget.h"
#include "Engine/DataTable.h"
#include "JK1InventoryEntryWidget.generated.h"

class USizeBox;
class UTextBlock;
class UImage;
class UJK1InventorySlotsWidget;
class UJK1ItemInstance;
class UJK1ItemDragWidget;
class AJK1Item;

USTRUCT(BlueprintType)
struct FJK1ItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AJK1Item> ItemClass;
};

/**
 * 
 */
UCLASS()
class JK1_API UJK1InventoryEntryWidget : public UJK1ItemWidget
{
	GENERATED_BODY()

public:
	UJK1InventoryEntryWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	void Init(UJK1InventorySlotsWidget* InSlotWidget, UJK1ItemInstance* InItemInstance, int32 InItemCount);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void RefreshWidgetOpacity(bool bClearlyVisible);
	void RefreshItemCount(int32 NewItemCount);

	UTexture2D* GetItemImage(int ItemId);

private:
	FIntPoint CachedFromSlotPos = FIntPoint::ZeroValue;
	FVector2D CachedDeltaWidgetPos = FVector2D::ZeroVector;
	int32 ItemCount = 0;

	UPROPERTY()
	class UDataTable* JK1ItemTable;
	
protected:
	UPROPERTY()
	TObjectPtr<UJK1InventorySlotsWidget> SlotsWidget;

	UPROPERTY()
	TObjectPtr<UJK1ItemInstance> ItemInstance;

	UPROPERTY()
	TSubclassOf<UJK1ItemDragWidget> DragWidgetClass;

	UPROPERTY()
	TSubclassOf<AJK1Item> ItemClass;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Count;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
	
	// 마우스를 올렸을 때 보이는 이미지
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Hover;
};
