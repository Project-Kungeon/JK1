// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_RegularPattern.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API UBTService_RegularPattern : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_RegularPattern();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	bool phase2;
};
