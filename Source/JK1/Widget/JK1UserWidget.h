// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JK1UserWidget.generated.h"

class UJK1CreatureStatComponent;

/**
 *
 */
UCLASS()
class JK1_API UJK1UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCreatureStat(UJK1CreatureStatComponent* StatComponent);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SetCreatureStat();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UJK1CreatureStatComponent> CurrentCreatureStat;

};