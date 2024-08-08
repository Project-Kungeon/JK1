// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
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
	void AttackAct();
	void SkillAct(const FInputActionValue& Value);

public:
	class UJK1PlayerHUD* GetPlayerWidget() const;
	void UpdateWidget();

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

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

	// Widget
	UPROPERTY()
	UJK1PlayerHUD* PlayerWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<UJK1PlayerHUD> HUDWidgetClass;

public:
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
};
