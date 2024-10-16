// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JK1DemoRaidMode.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1DemoRaidMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AJK1DemoRaidMode();

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	void RaidClear();

};
