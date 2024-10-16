// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include <stack>
#include "JK1PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AJK1PlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

	/*
	*  Member Function
	*/
	void JumpAct();
	void StopJumpingAct();
	void LookAct(const FInputActionValue& Value);
	void MoveAct(const FInputActionValue& Value);
	void StopAct(const FInputActionValue& Value);
	void AttackAct();
	void SkillAct(const FInputActionValue& Value);

	void ShowUI(const FInputActionValue& Value);
	

public:
	void InteractToObject();
	void ShowResurrection(bool ononff);
	class UJK1PlayerHUD* GetPlayerWidget() const;
	void UpdateWidget();
	void UpdateControlledCharacter();

	// InputSystem
	void AttachInputSystem();
	void RemoveInputSystem();

	// Lock On
	UFUNCTION(BlueprintCallable)
	void ToggleLockOn();
	UFUNCTION(BlueprintCallable)
	void EngagedLockOn();
	UFUNCTION(BlueprintCallable)
	void DisengagedLockOn();

	/*
	*  Member Variable
	*/
protected:
	UPROPERTY(EditAnywhere)
	ACharacter* ControlledCharacter;

	//InputMappingContext
	TObjectPtr <class UEnhancedInputLocalPlayerSubsystem> Subsystem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> BattleMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> UIMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> AttackMappingContext;

	//Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LockOnAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SkillAction;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> UIInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InterAction;

	// Widget
	UPROPERTY()
	UJK1PlayerHUD* PlayerWidget;
	UPROPERTY()
	UUserWidget* MenuWidget;
	UPROPERTY()
	UUserWidget* ResurrectionWidget;
	UPROPERTY()
	UUserWidget* InventoryWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<UJK1PlayerHUD> HUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> MenuWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> ResurrectionWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> InventoryWidgetClass;

public:
	TArray<UUserWidget*> OpenedWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InterActDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LockOnDistance;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> LockOnTargets;

	UPROPERTY(BlueprintReadWrite)
	AActor* TargetActor;

	UPROPERTY(BlueprintReadWrite)
	bool bLockOnEngaged;

	UPROPERTY(BlueprintReadWrite)
	bool bShouldRotate;

private:
	FInputModeGameOnly GameInputMode;
	FInputModeGameAndUI UIInputMode;

	FTimerHandle UnMoveHandler;
};
