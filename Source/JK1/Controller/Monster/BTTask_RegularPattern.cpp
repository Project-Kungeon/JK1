// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTTask_RegularPattern.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Creature/Monster/Boss/JK1Rampage.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "JK1LogChannels.h"

UBTTask_RegularPattern::UBTTask_RegularPattern()
{
	NodeName = TEXT("RegularPattern");
	bNotifyTick = true;
	phase2 = false;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_RegularPattern::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AJK1Rampage* ControllingPawn = Cast<AJK1Rampage>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	IsAttacking = true;
	ControllingPawn->OnGimmicEnd.AddLambda([=]() {
		IsAttacking = false;
		});

	if (!phase2)
	{
		ControllingPawn->Roar();
		if (ControllingPawn->CreatureStat->GetHPRatio() <= 0.4f)
		{
			UE_LOG(LogMonster, Log, TEXT("Enter to Phase2"));
			phase2 = true;
		}
	}
	else
	{
		ControllingPawn->EarthQuake();
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_RegularPattern::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!IsAttacking)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}
