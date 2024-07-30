// Copyright 2024 All Rights Reserved by J&K


#include "JK1PCAnimParryNotifyState.h"
#include "JK1PlayerCharacter.h"

void UJK1PCAnimParryNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AJK1PlayerCharacter* PlayerCharacter = Cast<AJK1PlayerCharacter>(MeshComp->GetOwner()))
	{
		PlayerCharacter->bParryActive = true;
	}
}

void UJK1PCAnimParryNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AJK1PlayerCharacter* PlayerCharacter = Cast<AJK1PlayerCharacter>(MeshComp->GetOwner()))
	{
		PlayerCharacter->bParryActive = false;
	}
}
