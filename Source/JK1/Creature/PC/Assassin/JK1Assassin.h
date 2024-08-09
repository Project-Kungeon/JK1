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
	//Skill Function
	virtual void SkillQ(const FInputActionValue& value) override;
	void SpawnDagger();
	void SkillQTrace();
	UFUNCTION()

	//Check Back Attack Fukction
	virtual void OnHit(AActor* Actor, FHitResult& HitResult);
	void SpawnHitEffect(const FVector& Location);
	virtual void SkillR(const FInputActionValue& Value) override;
	virtual void SkillLShift(const FInputActionValue& Value) override;

	UFUNCTION()
	void CheckWeaponTrace();
	

	//Cloaking
	void GetAndStoreMaterials();
	UFUNCTION()
	void TimelineProgress(float Value);
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
	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<class UParticleSystem> HitEffect;

	
	//Cloaking
	UPROPERTY(BlueprintReadWrite, Category = "Cloaking")
	bool IsCloaking; // Blueprint 노출 변수, 지울 예정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	TObjectPtr<class UMaterialInterface> CloakMaterial;
	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> DynamicMaterial;
	TArray<UMaterialInterface*> StoredMaterials;
	bool IsCloakingProcess = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timeline")
	float TimelineValue;
	TObjectPtr<class UCurveFloat> FloatCurve;
	UTimelineComponent* MyTimeline;
	

	//Dagger Spawning
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AActor> DaggerActor;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector SpawnLocation;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	FVector ThrowDirection;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float ThrowForce;
	UPROPERTY(EditAnywhere, Category = "CoolDown")
	float SkillQCoolDownTime;
	bool bCanThrow = true;


	

	
};
