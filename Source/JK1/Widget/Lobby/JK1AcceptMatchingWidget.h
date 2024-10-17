// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JK1AcceptMatchingWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class JK1_API UJK1AcceptMatchingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AcceptMatching();

	UFUNCTION(BlueprintCallable)
	void RefuseMatching();

	// 누군가 수락하면 true, 아니면 false
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ResultMatching(bool result);

	// 누군가 수락하면 true, 아니면 false
	UFUNCTION( BlueprintImplementableEvent)
	void InitWidget();
};
