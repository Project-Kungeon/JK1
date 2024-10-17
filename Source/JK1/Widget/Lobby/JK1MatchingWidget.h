// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JK1MatchingWidget.generated.h"

class UButton;
class UJK1WaitMatchingWidget;
class UJK1AcceptMatchingWidget;


DECLARE_DELEGATE_OneParam(FOnMatchingDelegate, bool);


/**
 * 
 */
UCLASS()
class JK1_API UJK1MatchingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	

	UFUNCTION(BlueprintCallable)
	void StartMatching();

	UFUNCTION(BlueprintCallable)
	void TryMatching();
	
	void UpdateAcceptWidget(bool IsAccpet);
	void MatchingFail();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_MatchingStart;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UJK1WaitMatchingWidget> WBP_WaitMatching;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UJK1AcceptMatchingWidget> WBP_AcceptMatching;

public:
	// Delegate
	FOnMatchingDelegate OnMatchingUpdate;
};
