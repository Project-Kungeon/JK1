// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "JK1RampageController.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1RampageController : public AAIController
{
	GENERATED_BODY()

public:
	AJK1RampageController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName CloseTargetKey;
	static const FName AggroTargetKey;
	static const FName PatternTypeKey;

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
	
};
