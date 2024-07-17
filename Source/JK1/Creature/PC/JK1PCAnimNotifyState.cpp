// Copyright 2024 All Rights Reserved by J&K


#include "JK1PCAnimNotifyState.h"
#include "JK1PlayerCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(JK1PCAnimNotifyState)

void UJK1PCAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AJK1PlayerCharacter* PlayerCharacter = Cast<AJK1PlayerCharacter>(MeshComp->GetOwner()))
	{
		PlayerCharacter->bWeaponActive = true;
	}
}

void UJK1PCAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AJK1PlayerCharacter* PlayerCharacter = Cast<AJK1PlayerCharacter>(MeshComp->GetOwner()))
	{
		PlayerCharacter->bWeaponActive = false;
		PlayerCharacter->WeaponAttackTargets.Empty();
	}
}
