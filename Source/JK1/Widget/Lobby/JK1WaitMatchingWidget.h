// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JK1WaitMatchingWidget.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API UJK1WaitMatchingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MatchingComplete();
	
};
