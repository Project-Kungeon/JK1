// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Creature/PC/Assassin/JK1Assassin.h"
#include "NJK1Assassin.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API ANJK1Assassin : public AJK1Assassin
{
	GENERATED_BODY()

public:
	ANJK1Assassin();
	~ANJK1Assassin();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

public:
	virtual void Attack() override;

	//Skill Function
	virtual void SkillQ(const FInputActionValue& value) override;
	void SpawnDagger(FVector SpawnPoint, FRotator SpawnRotation);
	virtual void SkillQTrace();

	//Check Back Attack Fukction
	virtual void OnHit(AActor* Actor, FHitResult& HitResult);
	void SpawnHitEffect(const FVector& Location);
	virtual void SkillR(const FInputActionValue& Value) override;
	virtual void SkillLShift(const FInputActionValue& Value) override;

	TArray<FHitResult> CheckWeaponTrace();
};
