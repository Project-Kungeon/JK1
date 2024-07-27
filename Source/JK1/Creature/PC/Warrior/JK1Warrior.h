// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1PlayerCharacter.h"
#include "JK1Warrior.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1Warrior : public AJK1PlayerCharacter
{
	GENERATED_BODY()

public:
	AJK1Warrior();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/*
	*  Member Function
	*/
protected:
	//Attack Funciton
	virtual void Attack() override;

	//ComboAction
	virtual void ComboActionBegin() override;
	virtual void DoCombo() override;
	virtual void ComboActionEnd() override;

public:
	//Skill Function
	virtual void SkillQ(const FInputActionValue& value) override;
	virtual void SkillE(const FInputActionValue& value) override;
	virtual void SkillR(const FInputActionValue& value) override;
	virtual void SkillLShift(const FInputActionValue& value) override;

	//refactoring
	UFUNCTION()
	TArray<FHitResult> CheckWeaponTrace();
	void PlayParticleSystem();
	void CheckSkillRTrace();
	void StopParticleSystem();


	/*
	*  Member Variable
	*/
protected:
	//Montage, 클래스들은 각자 기본공격 몽타주 갯수가 다르다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SkillRMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UParticleSystem> SkillREffect;

	UPROPERTY()
	UParticleSystemComponent* ParticleSystemComponent;
};
