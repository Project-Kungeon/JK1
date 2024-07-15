// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "JK1GameInstance.generated.h"

USTRUCT(BlueprintType)
struct FJK1CreatureData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FJK1CreatureData() : MaxHP(10.f), ATK(1.f), DEF(1.f), Exp(1.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float DEF;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Exp;
	// player -> requirement for next level
	// monster -> dropexp
};

/**
 * 
 */
UCLASS()
class JK1_API UJK1GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UJK1GameInstance();

	virtual void Init() override;

public:
	FJK1CreatureData* GetJK1PlayerData(FName ClassName);
	FJK1CreatureData* GetJK1MonsterData(FName Name);

private:
	UPROPERTY()
	class UDataTable* JK1PlayerTable;

	UPROPERTY()
	class UDataTable* JK1MonsterTable;
};