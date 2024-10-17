// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Widget/JK1ItemWidget.h"
#include "JK1ItemDragWidget.generated.h"

class UTexture2D;
class USizeBox;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class JK1_API UJK1ItemDragWidget : public UJK1ItemWidget
{
	GENERATED_BODY()

public:
	UJK1ItemDragWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void Init(const FVector2D& InWidgetSize, UTexture2D* InItemIcon, int32 InItemCount);

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Count;
	
};
