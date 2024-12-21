// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Widget/Login/LoginWidget.h"
#include "LoginGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API ALoginGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    ALoginGameModeBase();

    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class ULoginWidget> LoginWidgetClass;

private:
    UPROPERTY()
    class ULoginWidget* LoginWidget;
};
