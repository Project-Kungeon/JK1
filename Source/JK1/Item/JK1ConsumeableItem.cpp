// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1ConsumeableItem.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "JK1LogChannels.h"

AJK1ConsumeableItem::AJK1ConsumeableItem()
{
}

void AJK1ConsumeableItem::UseItem(AJK1PlayerCharacter* OwningPlayer)
{
	Super::UseItem(OwningPlayer);

	if (ItemID == 1)
		OwningPlayer->CreatureStat->SetCurrentHP(OwningPlayer->CreatureStat->GetCurrentHP() + 50.f);

	UE_LOG(LogItem, Log, TEXT("Use Comsumeable Item"));
}