// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JK1CreatureStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExpChangedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpDelegate);

class AJK1PlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JK1_API UJK1CreatureStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJK1CreatureStatComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	*  Member Function
	*/
public:
	// LoadData
	void SetOwner(bool OwnerType, FName ClassName) { IsPlayer = OwnerType; Name = ClassName; }
	void LoadData();

	// Battle System
	void SetImmunity(bool Onoff) { IsImmunity = Onoff; }
	void SetCurrentHP(float NewHP);
	void SetStat(int index, float value);
	void PlusExp(float Exp);
	void LevelUP(int level);
	bool HitDamage(float NewDamage, AController* instigator);
	float TotalDamageBy(AController* instigator);

	// For Widget
	UFUNCTION(BlueprintCallable)
	FName GetCharacterName();
	UFUNCTION(BlueprintCallable)
	float GetCurrentHP();
	UFUNCTION(BlueprintCallable)
	float GetMaxHp();
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentLevel();
	UFUNCTION(BlueprintCallable)
	float GetHPRatio();
	UFUNCTION(BlueprintCallable)
	float GetExpRatio();
	

	/*
	*  Member Variable
	*/
public:
	// Delegate
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnHPIsZeroDelegate OnHPIsZero;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnHPChangedDelegate OnHPChanged;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnExpChangedDelegate OnExpChanged;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnLevelUpDelegate OnLevelUp;

private:
	bool IsPlayer;
	bool IsImmunity;
	
	// Stat Data
	struct FJK1CreatureData* BasicStatData;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	FName Name;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentExp;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 CurrentLevel;
	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentStat[2];

	// 데미지 입힌 대상
	TMultiMap<AController*, float> DamageInstigator;
};
