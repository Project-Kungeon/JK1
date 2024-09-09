// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Creature/PC/Archor/JK1Archor.h"
#include "NJK1Archor.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API ANJK1Archor : public AJK1Archor
{
	GENERATED_BODY()
	
public:
	ANJK1Archor();
	~ANJK1Archor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void DoCombo() override;

	virtual void SkillQ(const FInputActionValue& value) override;
	virtual void SkillE(const FInputActionValue& value) override;
	virtual void SkillR(const FInputActionValue& value) override;
	virtual void SkillLShift(const FInputActionValue& value) override;

	virtual void OnArrowHit(FHitResult hit) override;
	virtual void OnArchorQ_Hit(FHitResult hit) override;
	virtual void OnArchorE_Hit(TArray<FHitResult> hits) override;

	virtual void ShootNRecovery() override;
};
