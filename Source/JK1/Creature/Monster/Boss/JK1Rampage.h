// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Creature/Monster/JK1MonsterBase.h"
#include "JK1Rampage.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnGimmicEndDelegate);

/**
 * 
 */
UCLASS()
class JK1_API AJK1Rampage : public AJK1MonsterBase
{
	GENERATED_BODY()

public:
	AJK1Rampage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Attack Pattern
	void GiveStatusEffect(int type);
	void BasicAttack();
	void Roar();
	void EarthQuake();
	void GroundSmash();
	void ThrowAway();
	void EnhancedAttack();

	UFUNCTION()
	virtual void CheckBATrace() override;
	virtual void CheckFistTrace();

	virtual void Death() override;

	/*
	*  Member Variable
	*/
public:
	FTimerHandle AnimHandle;

	bool FistType;

	// Montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> RoarMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> EnhancedAttackMontage;

	FOnAttackEndDelegate OnAttackEnd;
	FOnGimmicEndDelegate OnGimmicEnd;
};
