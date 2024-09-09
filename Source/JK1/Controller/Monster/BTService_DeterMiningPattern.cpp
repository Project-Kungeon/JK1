// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTService_DeterMiningPattern.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/Monster/Boss/JK1Rampage.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_DeterMiningPattern::UBTService_DeterMiningPattern()
{
	NodeName = TEXT("DeterMiningPattern");
	Interval = 30.0f;
}

void UBTService_DeterMiningPattern::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// close와 far 중 더 데미지 많이 입힌 쪽으로

	AJK1Rampage* ControllingPawn = Cast<AJK1Rampage>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return;

	auto aggro = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AJK1RampageController::AggroTargetKey));
	if (aggro != nullptr)
	{
		float Distance = FVector::Distance(ControllingPawn->GetActorLocation(), aggro->GetActorLocation());

		// if close -> 원거리 기술 On
		if (Distance >= 500.f)
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AJK1RampageController::PatternTypeKey, true);
		else
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AJK1RampageController::PatternTypeKey, false);
	}
	return;
}
