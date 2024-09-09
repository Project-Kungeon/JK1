// Copyright 2024 All Rights Reserved by J&K


#include "Controller/Monster/BTService_Detect.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/Monster/Boss/JK1Rampage.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 5.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AJK1Rampage* ControllingPawn = Cast<AJK1Rampage>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return;

	ControllingPawn->DetectTargets.Empty();

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 1000.f;
	if (World == nullptr)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	// 1단계 타겟 플레이어 감지
	if (bResult)
	{	
		for (auto const& OverlapResult : OverlapResults)
		{
			if (AJK1PlayerCharacter* PlayerCharacter = Cast<AJK1PlayerCharacter>(OverlapResult.GetActor()))
			{
				// 은신 상태 아닌 애들만 감지
				// 문제는 감지된 이후 은신쓰면 이미 감지된 상태라 어그로 안풀림
				// 델리게이트로 은신 진입 시 해제해줘야할지 고민중
				if (!(PlayerCharacter->GetCurrectStatusEffect() & (1 << 3)))
					ControllingPawn->DetectTargets.Emplace(PlayerCharacter);
			}
		}
	}

	if (ControllingPawn->DetectTargets.IsEmpty())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AJK1RampageController::CloseTargetKey, nullptr);

		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
		return;
	}

	// 2단계 가장 가까운 타겟, 가장 센 타겟
	float ClosestDistance = FLT_MAX;
	float DamagebyPlayer = FLT_MIN;

	for (AJK1PlayerCharacter* DetectTarget : ControllingPawn->DetectTargets)
	{
		if (DetectTarget /* && DetectTarget->GetController()->IsPlayerController() */ )
		{
			float DamagebyTarget = ControllingPawn->CreatureStat->TotalDamageBy(DetectTarget->GetController());
			if (DamagebyPlayer < DamagebyTarget)
			{
				DamagebyPlayer = DamagebyTarget;
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AJK1RampageController::AggroTargetKey, DetectTarget);
			}

			float Distance = FVector::Distance(ControllingPawn->GetActorLocation(), DetectTarget->GetActorLocation());
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AJK1RampageController::CloseTargetKey, DetectTarget);
			}			
			DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
			DrawDebugPoint(World, DetectTarget->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
			DrawDebugLine(World, ControllingPawn->GetActorLocation(), DetectTarget->GetActorLocation(), FColor::Blue, false, 0.2f);
		}
	}

	//if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(AJK1RampageController::CloseTargetKey) != nullptr)
	//	UE_LOG(LogMonster, Log, TEXT("Detect Target"));
	
	return;
	
}

void UBTService_Detect::DetectTarget()
{
}


