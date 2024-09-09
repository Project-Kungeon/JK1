// Copyright 2024 All Rights Reserved by J&K


#include "Creature/AnimNotify/JK1MonsterSkillNotifyState.h"
#include "Creature/Monster/Boss/JK1Rampage.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(JK1MonsterSkillNotifyState)

void UJK1MonsterSkillNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UJK1MonsterSkillNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AJK1Rampage* Creature = Cast<AJK1Rampage>(MeshComp->GetOwner()))
	{
		Creature->FistType = !(Creature->FistType);
	}
}

void UJK1MonsterSkillNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (AJK1Rampage* Creature = Cast<AJK1Rampage>(MeshComp->GetOwner()))
	{
		Creature->CheckFistTrace();
	}
}
