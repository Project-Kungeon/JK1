// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTDecorator_IsInAttackRange.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
	AttackRange = 200.0f;
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return false;

	auto Target = Cast<AJK1PlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AJK1RampageController::TargetKey));
	if (Target == nullptr)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRange);
	return bResult;
}
