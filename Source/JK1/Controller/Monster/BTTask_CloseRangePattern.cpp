// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTTask_CloseRangePattern.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Creature/Monster/Boss/JK1Rampage.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CloseRangePattern::UBTTask_CloseRangePattern()
{
	NodeName = TEXT("CloseRangePattern");
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_CloseRangePattern::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	IsAttacking = true;

	AJK1Rampage* ControllingPawn = Cast<AJK1Rampage>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	ControllingPawn->OnGimmicEnd.AddLambda([=]() {
		IsAttacking = false;
		});

	// basic attack 가능한 대상이 있을 때 
	// 어그로 타겟 거리가 500 이상 일 경우 가까운 대상 집어 던지기
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AJK1RampageController::PatternTypeKey))
		ControllingPawn->ThrowAway();
	// 어그로 타겟 거리가 500 미만 일 경우 강화공격
	else
		ControllingPawn->EnhancedAttack();

	return EBTNodeResult::InProgress;
}

void UBTTask_CloseRangePattern::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(!IsAttacking)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
