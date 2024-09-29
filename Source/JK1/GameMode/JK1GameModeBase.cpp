// Copyright Epic Games, Inc. All Rights Reserved.


#include "JK1GameModeBase.h"
#include "Item/JK1InventorySubsystem.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"

void AJK1GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UJK1InventorySubsystem* Inventory = Cast<UJK1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UJK1InventorySubsystem::StaticClass()));
	if (Inventory)
	{
		Inventory->AddNewItem(1);
	}
}
