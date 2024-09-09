// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTTask_TurnToTarget.h"
#include "Creature/Monster/Boss/JK1Rampage.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "JK1RampageController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("TurnToTarget");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	AJK1Rampage* RP = Cast<AJK1Rampage>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == RP)
		return EBTNodeResult::Failed;

	AJK1PlayerCharacter* Target = Cast<AJK1PlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AJK1RampageController::CloseTargetKey));
	if(nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - RP->GetActorLocation();
	LookVector.Z = 0.0f;

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	//RP->SetActorRotation(FMath::RInterpTo(RP->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 20.0f));
	RP->SetActorRotation(TargetRot);

	return EBTNodeResult::Succeeded;
}
