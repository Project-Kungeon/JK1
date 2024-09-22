// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1CreatureBase.h"
#include "InputActionValue.h"
#include "JK1PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResurrectionDelegate);
/**
 * 
 */
UCLASS()
class JK1_API AJK1PlayerCharacter : public AJK1CreatureBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJK1PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/*
	* Member Function
	*/
public:
	//Move and Look 
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	//Attack 
	virtual void Attack();

	UFUNCTION(BlueprintCallable)
	virtual void ComboActionBegin();
	UFUNCTION(BlueprintCallable)
	virtual void DoCombo();
	UFUNCTION(BlueprintCallable)
	virtual void ComboActionEnd();

	//Skill 
	virtual void SkillQ(const FInputActionValue& Value);
	virtual void SkillE(const FInputActionValue& Value);
	virtual void SkillR(const FInputActionValue& Value);
	virtual void SkillLShift(const FInputActionValue& Value);

	virtual void Death() override;

	UFUNCTION(BlueprintCallable)
	void Resurrection();

	/*
	* Member Variable
	*/
protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;

	class AJK1PlayerController* PlayerController;
	class AJK1DemoRaidState* DemoRaidState;

public:
	// Delegate
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnResurrectionDelegate OnResurrection;

public:
	UPROPERTY(BlueprintReadWrite)
	bool bWeaponActive;

	/* 타이밍에 맞게 입력하는 패링으로 수정 */
	UPROPERTY(BlueprintReadWrite)
	bool bParryActive = false;

	UPROPERTY()
	TSet<AActor*> WeaponAttackTargets;

	uint8 IsAttacking : 1;
	uint8 SaveAttacking : 1;
	int32 MaxCombo;
};
