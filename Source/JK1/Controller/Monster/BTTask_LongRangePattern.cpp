// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTTask_LongRangePattern.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Creature/Monster/Boss/JK1Rampage.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_LongRangePattern::UBTTask_LongRangePattern()
{
	NodeName = TEXT("LongRangePattern");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_LongRangePattern::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AJK1Rampage* ControllingPawn = Cast<AJK1Rampage>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	// basic attack 가능한 대상이 없을 때 
	// 어그로 타겟 거리가 500 이상일 때 날아가기
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AJK1RampageController::PatternTypeKey))
		ControllingPawn->GroundSmash();
	// 어그로 타겟 거리가 500 미만일 때 집어던지기
	else
		ControllingPawn->ThrowAway();

	return EBTNodeResult::InProgress;
}

void UBTTask_LongRangePattern::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// TODO : Rampage에서 공격완료 표시를 델리게이트로 확인하면 일이 끝났다고 표시
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
