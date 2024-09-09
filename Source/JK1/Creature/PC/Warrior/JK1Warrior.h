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
	virtual void CheckBATrace() override;
	void PlayParticleSystem();
	void DealDamageOverTime();
	void StartROverTime();
	void CheckSkillRTrace();
	void StopParticleSystem();
	void ResetSkillCooldown();
	//void ResetSkillLShift();
	//void bCanUseSkillActive() { bCanUseSkill = true; };
	//삭제해야하는 테스트용 함수.
	void SetParryActiveTrue() { bParryActive = true; };
	void SetParryActiveFalse() { bParryActive = false; };
	
	


	/*
	*  Member Variable
	*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> CurrentMontage;

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
	TObjectPtr<class UAnimMontage> SkillEMontage_Intro;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SkillEMontage_HitReact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SkillLShiftMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UParticleSystem> SkillREffect;

	UPROPERTY()
	TObjectPtr<class UParticleSystemComponent> ParticleSystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DashDistance=1000.f;

	// Dash duration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DashDuration=1.f;

	// Timer handle for controlling dash duration
	FTimerHandle DashTimerHandle;

	// Current speed of the dash
	FVector DashVelocity;
	
	float SkillCooldown;
	FTimerHandle SkillCooldownTimerHandle;
	uint32 ParryCount = 0;
	UAnimInstance* AnimInstance = nullptr;
	// 데미지 처리 주기
	const float DamageInterval = 0.5f;
	// 데미지 주기 지속 시간
	const float DamageDuration = 5.0f;

	// 총 데미지 지속 시간 동안 남은 시간
	float RemainingDamageTime;

	FTimerHandle DamageTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpStrength = 400.0f;

	// Forward movement strength when jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ForwardStrength = 1000.0f;
};
