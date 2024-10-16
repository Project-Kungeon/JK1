// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1PlayerCharacter.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "JK1Assassin.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1Assassin : public AJK1PlayerCharacter
{
	GENERATED_BODY()

public:
	AJK1Assassin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

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
	virtual void	OnBasicAttackHit(TArray<FHitResult> HitResults);
	//Skill Function
	virtual void SkillQ(const FInputActionValue& value) override;
	void SpawnDagger(FVector SpawnPoint, FRotator SpawnRotation);
	virtual void SkillQTrace();
	UFUNCTION()

	//Check Back Attack Fukction
	virtual bool IsBackAttack(AActor* Actor, FHitResult& HitResult);
	void SpawnHitEffect(const FVector& Location);
	virtual void SkillR(const FInputActionValue& Value) override;
	void CheckCharacterMovement();
	virtual void SkillLShift(const FInputActionValue& Value) override;

	void AssassinQ(FVector SpawnPoint, FRotator SpawnRotation);
	void AssassinE(FVector HitLocation);	// 평타 강화
	void AssassinR();
	void AssassinLSOn();
	void AssassinLSOff();

	virtual void OnAssassinQ_Hit(FHitResult hit);


	UFUNCTION()
	virtual void CheckBATrace() override; 
	

	//Cloaking
	void GetAndStoreMaterials();
	UFUNCTION()
	void TimelineProgress(float Value);

	//SkillCooldownFunction
	virtual void StartQTimer() override;
	virtual void StartRTimer() override;
	virtual void StartLSTimer() override;
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

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<class UParticleSystem> HitEffect;

	
	//Cloaking
	UPROPERTY(BlueprintReadWrite, Category = "Cloaking")
	bool IsCloaking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	TObjectPtr<class UMaterialInterface> CloakMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> DynamicMaterial;

	TArray<UMaterialInterface*> StoredMaterials;

	bool IsCloakingProcess = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timeline")
	float TimelineValue;

	TObjectPtr<class UCurveFloat> CloakCurve;
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> MyTimeline;
	

	//Dagger Spawning
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> DaggerActor;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector SpawnLocation;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector ThrowDirection;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float ThrowForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")

	bool bCanThrow = true;

private:

	//Assassin Skill Cool Time
	const float AssassinQCT = 3.f;
	const float AssassinRCT = 30.f;
	const float AssassinLSCT = 15.f;

	//Assassin Buff Time
	const float LSBuffTime = 5.f;

	
};
