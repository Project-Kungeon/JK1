// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTService_RegularPattern.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Creature/Monster/Boss/JK1Rampage.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "JK1LogChannels.h"

UBTService_RegularPattern::UBTService_RegularPattern()
{
	NodeName = TEXT("RegularPattern");
	Interval = 30.0f;	
	phase2 = false;
}

void UBTService_RegularPattern::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AJK1Rampage* ControllingPawn = Cast<AJK1Rampage>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return;
	
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
}
