// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/JK1RampageController.h"
#include "JK1LogChannels.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AJK1RampageController::HomePosKey(TEXT("HomePos"));
const FName AJK1RampageController::PatrolPosKey(TEXT("PatrolPos"));
const FName AJK1RampageController::TargetKey(TEXT("Target"));

AJK1RampageController::AJK1RampageController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprints/Creature/Monster/AI/BB_Rampage.BB_Rampage'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprints/Creature/Monster/AI/BT_Rampage.BT_Rampage'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AJK1RampageController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComp = Blackboard;
	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogMonster, Warning, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}
