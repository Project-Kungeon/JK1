// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JK1LobbyWidget.generated.h"

class UButton;
class UHorizontalBox;
/**
 *
 */
UCLASS()
class JK1_API UJK1LobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	void CharacterChoice();

	UFUNCTION(BlueprintCallable)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetClose();

	void MapChange();

protected:
	UPROPERTY(BlueprintReadWrite)
	int32 index;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	FName TransferLevelName;

	bool IsOpen;

	TObjectPtr<UButton> Btn_Character;

	TObjectPtr<UButton> Btn_GameStart;

	TObjectPtr<UHorizontalBox> BtnBox;
};