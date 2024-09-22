// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "JK1DemoRaidState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathCountDelegate);
/**
 * 
 */
UCLASS()
class JK1_API AJK1DemoRaidState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AJK1DemoRaidState();

public:
	int32	GetDeathCount() { return DeathCount; }
	void	UseDeathCount();

public:
	FOnDeathCountDelegate OnDeathCountChange;

private:
	UPROPERTY(Transient)
	int32 DeathCount;

};
