// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1CreatureBase.h"
#include "InputActionValue.h"
#include "JK1PlayerCharacter.generated.h"

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

	//Temp Code
	//Skill Cooldown Time Getter Setter func
	float GetQ() { return SkillQCool; }
	float GetE() { return SkillECool; }
	float GetR() { return SkillRCool; }
	float GetLS() { return SkillLSCool; }

	void SetQ(float Q) { SkillQCool = Q; }
	void SetE(float E) { SkillECool = E; }
	void SetR(float R) { SkillRCool = R; }
	void SetLS(float LS) { SkillLSCool = LS; }

	virtual void StartQTimer();
	virtual void StartETimer();
	virtual void StartRTimer();
	virtual void StartLSTimer();


	/*
	* Member Variable
	*/

protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;

	class AJK1PlayerController* PlayerController;

	//Cooldown Timer handle
	FTimerHandle Qhandler;
	FTimerHandle Ehandler;
	FTimerHandle Rhandler;
	FTimerHandle LShandler;

	UPROPERTY(BlueprintReadOnly)
	float SkillQCool;
	UPROPERTY(BlueprintReadOnly)
	float SkillECool;
	UPROPERTY(BlueprintReadOnly)
	float SkillRCool;
	UPROPERTY(BlueprintReadOnly)
	float SkillLSCool;


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
