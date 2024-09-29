// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1ConsumeableItem.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/JK1CreatureStatComponent.h"

AJK1ConsumeableItem::AJK1ConsumeableItem()
{
}

void AJK1ConsumeableItem::UseItem(AJK1PlayerCharacter* OwningPlayer)
{
	Super::UseItem(OwningPlayer);
}

void AJK1ConsumeableItem::InterActive()
{
	Super::InterActive();
}
