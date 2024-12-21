// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/EditableText.h>
#include <Components/TextBlock.h>
#include "RegisterWidget.generated.h"

class ULoginWidget;
/**
 * 
 */
UCLASS()
class JK1_API URegisterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnRegisterButtonClicked();	// ȸ������ ��ư Ŭ��

	UFUNCTION(BlueprintCallable)
	void OnBackButtonClicked();  // �α��� ȭ������ ���ư���

public:
	void SetLoginWidget(ULoginWidget* Widget) { LoginWidget = Widget; }

private:
	bool RegisterNewUser(FString InputID, FString InputPassword);

private:
	UPROPERTY()
	ULoginWidget* LoginWidget;

private:
	UPROPERTY(meta = (BindWidget))
	UEditableText* IDEditableText;

	UPROPERTY(meta = (BindWidget))
	UEditableText* PasswordEditableText;

	UPROPERTY(meta = (BindWidget))
	UEditableText* ConfirmPasswordEditableText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ErrorMessageText;
};
