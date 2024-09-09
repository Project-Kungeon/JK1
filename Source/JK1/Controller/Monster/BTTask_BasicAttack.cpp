// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTTask_BasicAttack.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Creature/Monster/Boss/JK1Rampage.h"
#include "JK1LogChannels.h"

UBTTask_BasicAttack::UBTTask_BasicAttack()
{
	NodeName = TEXT("BasicAttack");
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_BasicAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AJK1Rampage* ControllingPawn = Cast<AJK1Rampage>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	ControllingPawn->OnAttackEnd.AddLambda([=]() {
		IsAttacking = false;
		});

	IsAttacking = true;
	ControllingPawn->BasicAttack();
	
	return EBTNodeResult::InProgress;
}

void UBTTask_BasicAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(!IsAttacking)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
