// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JK1.h"
#include "JK1CreatureStatComponent.generated.h"

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
	void SetOwner(bool OwnerType, FName ClassName) { IsPlayer = OwnerType; Name = ClassName; }
	void LoadData();
	void SetHP(float NewHP);
	void SetStat(int index, float value);
	void PlusExp(float Exp);

	void HitDamage(float NewDamage);

	/*
	 * Network Function 
	 */
public:
	void SetObjectInfo(message::ObjectInfo Info);
	void SetCreatureInfo(message::CreatureInfo Info);
	message::ObjectInfo* GetObjectInfo() { return this->ObjectInfo; }
	message::CreatureInfo* GetCreatureInfo() { return this->CreatureInfo; }

public:
	float GetHP() { return this->CurrentHP; }

	/*
	*  Member Variable
	*/
private:
	bool IsPlayer;
	struct FJK1CreatureData* BasicStatData;

	message::ObjectInfo* ObjectInfo;
	message::CreatureInfo* CreatureInfo;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	FName Name;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int Level;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentExp;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentStat[2];

	// 데미지 입힌 대상
	//TArray<AJK1PlayerController*> DamageInstigator;
};
