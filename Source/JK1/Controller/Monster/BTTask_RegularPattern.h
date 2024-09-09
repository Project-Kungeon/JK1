// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RegularPattern.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API UBTTask_RegularPattern : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_RegularPattern();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool phase2;	
	bool IsAttacking;
};
