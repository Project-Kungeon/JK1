// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../JK1LogChannels.h"
#include "JK1CreatureBase.generated.h"

UCLASS()
class JK1_API AJK1CreatureBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJK1CreatureBase();

protected:
	// Called when the game starts or when spawned
	virtual void	BeginPlay() override;

	/*
	*   Member Function
	*/
public:	
	// Called every frame
	virtual void	Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void	SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float	TakeDamage(float damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCursor) override;
	virtual void	PossessedBy(AController* NewController) override;
	virtual void	CheckBATrace();	// BasicAttack

	unsigned char	GetCurrectStatusEffect() { return statusEffect; }
	void			ChangeStatusEffect(bool On, int status);
	void			ApplyStatusEffect();

	void			ApplyDamageToTarget(TArray<FHitResult> HitResults, float damage);
	UFUNCTION()
	virtual void Death();
	/*
	*  Member Variable
	*/ 
public:
	// combo == 0 not start 
	// combo >= 1 -> Combo Start
	int32 CurrentCombo = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bBAActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	TObjectPtr<class UJK1CreatureStatComponent> CreatureStat;

	UPROPERTY()
	TSet<AActor*> BasicAttackTargets;

private:
	// 0000|0000 : 은신, 기절, 이속감소, 면역
	unsigned char statusEffect;

	
};
