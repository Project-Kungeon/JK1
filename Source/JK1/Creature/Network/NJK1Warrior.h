// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Creature/PC/Warrior/JK1Warrior.h"
#include "JK1.h"
#include "Kismet/KismetMathLibrary.h"
#include "NJK1Warrior.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API ANJK1Warrior : public AJK1Warrior
{
	GENERATED_BODY()
public:
	ANJK1Warrior();
	~ANJK1Warrior();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//Move and Look Function
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

	//Attack Function
	virtual void Attack();
	virtual void	OnBasicAttackHit(TArray<FHitResult> HitResults);

	virtual void ComboActionBegin() override;
	virtual void DoCombo() override;
	virtual void ComboActionEnd() override;

	//Skill 
	virtual void SkillQ(const FInputActionValue& Value) override;
	virtual void SkillE(const FInputActionValue& Value) override;
	virtual void SkillR(const FInputActionValue& Value) override;
	virtual void SkillLShift(const FInputActionValue& Value) override;


	virtual void CheckDamagedInParry() override;

	// Warrior
	virtual void DealDamageOverTime();
	virtual void StartROverTime();

	//refactoring

	/*
	 * Network Module
	 */


};
