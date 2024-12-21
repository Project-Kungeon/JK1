// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/EditableText.h>
#include <Components/TextBlock.h>

#include "LoginWidget.generated.h"

class URegisterWidget;
/**
 * 
 */
UCLASS()
class JK1_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnLoginButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnRegisterButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class URegisterWidget> RegisterWidgetClass;

	bool ValidateLoginInfo(const FString& ID, const FString& Password);

private:
	UPROPERTY(meta = (BindWidget))
	UEditableText* IDEditableText;

	UPROPERTY(meta = (BindWidget))
	UEditableText* PasswordEditableText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ErrorMessageText;

	
};
