// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1PlayerCharacter.h"
#include "JK1Archor.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1Archor : public AJK1PlayerCharacter
{
	GENERATED_BODY()
public:
	AJK1Archor();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	//Attack Funciton
	virtual void Attack() override;
	void Shoot();

	//ComboAction
	virtual void ComboActionBegin() override;
	virtual void DoCombo() override;
	virtual void ComboActionEnd() override;

public:
	//Skill Function
	virtual void SkillQ(const FInputActionValue& value) override;

	UFUNCTION()
	void CheckWeaponTrace();

protected:
	//Montage, 클래스들은 각자 기본공격 몽타주 갯수가 다르다.
	//Archor는 활을 쏘는 모션 하나.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage;
	
};
