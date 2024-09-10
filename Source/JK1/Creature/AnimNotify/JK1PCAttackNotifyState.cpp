// Copyright 2024 All Rights Reserved by J&K


#include "JK1PCAttackNotifyState.h"
#include "../JK1CreatureBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(JK1PCAttackNotifyState)

void UJK1PCAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	if (AJK1CreatureBase* Creature = Cast<AJK1CreatureBase>(MeshComp->GetOwner()))
	{
		Creature->bBAActive = true;
	}
}

void UJK1PCAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AJK1CreatureBase* Creature = Cast<AJK1CreatureBase>(MeshComp->GetOwner()))
	{
		Creature->bBAActive = false;
		Creature->BasicAttackTargets.Empty();
		Creature->CurrentCombo++;
	}
}

void UJK1PCAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (AJK1CreatureBase* Creature = Cast<AJK1CreatureBase>(MeshComp->GetOwner()))
	{
		Creature->CheckBATrace();
	}
}
