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
	virtual void	OnBasicAttackHit(TArray<FHitResult> HitResults);

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

	// Warrior
	virtual void WarriorQ();
	virtual void WarriorE();
	virtual void WarriorE_Success();
	virtual void WarriorR();
	virtual void WarriorLShift(FVector ForwardDirection);

	UFUNCTION()
	virtual void CheckDamagedInParry();

	//refactoring
	UFUNCTION()
	virtual void CheckBATrace() override;
	void PlayParticleSystem();
	virtual void DealDamageOverTime();
	virtual void StartROverTime();
	TArray<FOverlapResult> CheckSkillRTrace();
	void StopParticleSystem();

	UFUNCTION(BlueprintCallable)
	void ResetSkillCooldown();
	
	//SkillCooldownFunction
	virtual void StartQTimer() override;
	virtual void StartETimer() override;
	virtual void StartRTimer() override;
	virtual void StartLSTimer() override;

	bool GetbParryCount() { return bParryCount; }
	void SetbParryCount(bool _bParryCount) { bParryCount = _bParryCount; }
	
	void ChangeStatus();
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
	TObjectPtr<class UAnimMontage> SkillQMontage;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<class UBoxComponent> CollisionComponent;

	// Timer handle for controlling dash duration
	FTimerHandle DashTimerHandle;

	// Current speed of the dash
	FVector DashVelocity;
	
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

protected:
	 
	//Warrior Skill Cool Time
	const float WarriorQCT = 3.f;
	const float WarriorECT = 30.f;
	const float WarriorRCT = 15.f;
	const float WarriorLSCT = 10.f;

	//Warrior Buff Time
	const float QBuffTime = 3.f;
	const float RBuffTime = 5.f;
	
	// Check Success Parry Count
	uint32 ParryCount = 0;
	//Check IS SkillQ Activate
	bool bQActive = false;
	//Check Already add Check Parry Count
	bool bParryCount = false;

	
};
