// Copyright 2024 All Rights Reserved by J&K


#include "JK1PCAnimParryNotifyState.h"
#include "JK1PlayerCharacter.h"
#include "JK1/Creature/JK1CreatureStatComponent.h"
#include "Creature/PC/Warrior/JK1Warrior.h"

void UJK1PCAnimParryNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AJK1Warrior* warrior = Cast<AJK1Warrior>(MeshComp->GetOwner()))
	{
		warrior->bParryActive = true;
		warrior->CreatureStat->SetIsParry(true);
	}
}

void UJK1PCAnimParryNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AJK1Warrior* warrior = Cast<AJK1Warrior>(MeshComp->GetOwner()))
	{
		warrior->bParryActive = false;
		warrior->CreatureStat->SetIsParry(false);
	}
}
