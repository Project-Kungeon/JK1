// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API UBTTask_BasicAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_BasicAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	bool IsAttacking = false;
};
