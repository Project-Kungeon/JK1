// Copyright 2024 All Rights Reserved by J&K

#pragma once

UENUM(BlueprintType)
enum class ECreatureState : uint8
{
	None,
	Moving,
	Skill,
	Dead,
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Junk,
	Poor,
	Common,
	UnCommon,
	Rare,
	Epic,
	Legendary,
	Unique,

	Count	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Equipment,
	Consumable,
	Other,
};

namespace Item
{
	const FIntPoint UnitInventorySlotSize = FIntPoint(50.f, 50.f);
}