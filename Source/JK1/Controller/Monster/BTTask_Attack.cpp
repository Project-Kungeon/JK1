// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTTask_Attack.h"
#include "JK1LogChannels.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	UE_LOG(LogMonster, Warning, TEXT("Attack!"));
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// TODO : Rampage에서 공격이 끝난걸 델리게이트로 받은걸 확인하면 일이 끝났다고 표시
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
