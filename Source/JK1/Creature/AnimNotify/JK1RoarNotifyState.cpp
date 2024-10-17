// Copyright 2024 All Rights Reserved by J&K


#include "Creature/AnimNotify/JK1RoarNotifyState.h"
#include "../Monster/JK1MonsterBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(JK1RoarNotifyState)

void UJK1RoarNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AJK1MonsterBase* RP = Cast<AJK1MonsterBase>(MeshComp->GetOwner()))
	{
		RP->GiveStatusEffect(1);
	}
}

void UJK1RoarNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AJK1MonsterBase* RP = Cast<AJK1MonsterBase>(MeshComp->GetOwner()))
	{
		
	}
}
