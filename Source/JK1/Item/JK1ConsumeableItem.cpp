// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1ConsumeableItem.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "JK1.h"

UJK1ConsumeableItem::UJK1ConsumeableItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UJK1ConsumeableItem::UseItem()
{
	Super::UseItem();
	if (auto player = _Owner.Get())
	{
		game::item::C_Item_ConsumeableUsed pkt;

		pkt.set_player_id(player->CreatureStat->GetCreatureInfo()->object_info().object_id());
		pkt.set_used_item_id(_ItemInfo->item_id());

		SEND_PACKET(message::HEADER::ITEM_CONSUMEABLE_USED_REQ, pkt);
		return true;
	}

	return false;


}