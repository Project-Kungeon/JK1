// Copyright 2024 All Rights Reserved by J&K


#include "Item/JK1ItemInstance.h"
#include "Item/JK1InventorySubsystem.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Network/Item.pb.h"
#include "System/NetworkJK1GameInstance.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/JK1CreatureStatComponent.h"

AJK1ItemInstance::AJK1ItemInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, _objectInfo(new message::ObjectInfo())
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AJK1ItemInstance::BeginPlay()
{
	Super::BeginPlay();
}

void AJK1ItemInstance::Init(int32 InItemID, EItemType type, EItemRarity Rarity)
{
	//if (InItemID <= 0)
	//	return;

	//ItemID = InItemID;
	//ItemCount = 1;
	//Itemtype = type;
	//ItemRarity = Rarity;
}

void AJK1ItemInstance::Init(message::ItemObjectInfo itemObjectInfo)
{
	_itemType = itemObjectInfo.item_type();
	_objectInfo->CopyFrom(itemObjectInfo.object_info());
}

//void AJK1ItemInstance::UseItem(AJK1PlayerCharacter* OwningPlayer)
//{
//	if (Itemtype != EItemType::Consumable)
//		return;
//}

void AJK1ItemInstance::InterActive()
{
	game::item::C_Item_PickedUp pkt;
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(GetGameInstance()))
	{
		pkt.set_player_id(GameInstance->MyPlayer->CreatureStat->GetCreatureInfo()->object_info().object_id());
		pkt.set_picked_object_id(_objectInfo->object_id());
		SEND_PACKET(message::HEADER::ITEM_PICKED_UP_REQ, pkt);
	}

	//UJK1InventorySubsystem* Inventory = Cast<UJK1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UJK1InventorySubsystem::StaticClass()));
	//if (Inventory)
	//{
	//	Inventory->AddNewItem(ItemID);
	//}
}
