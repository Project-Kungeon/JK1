// Copyright 2024 All Rights Reserved by J&K

#include "JK1DemoRaidMode.h"
#include "Controller/Player/JK1PlayerController.h"
#include "GameMode/DemoRaid/JK1DemoRaidState.h"
#include "Creature/JK1CreatureBase.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "Creature/PC/Warrior/JK1Warrior.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"
#include "Item/JK1InventorySubsystem.h"

AJK1DemoRaidMode::AJK1DemoRaidMode()
{
	static ConstructorHelpers::FClassFinder<AJK1PlayerCharacter> player(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Creature/PC/Warrior/BP_JK1Warrior.BP_JK1Warrior_C'"));
	if(player.Succeeded())
		DefaultPawnClass = player.Class;

	PlayerControllerClass = AJK1PlayerController::StaticClass();
	GameStateClass = AJK1DemoRaidState::StaticClass();
}

void AJK1DemoRaidMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UJK1InventorySubsystem* Inventory = Cast<UJK1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UJK1InventorySubsystem::StaticClass()));
	if (Inventory)
	{
		Inventory->AddNewItem(1);
	}
}

void AJK1DemoRaidMode::RaidClear()
{
	// Player들에게 보상
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const auto Player = Cast<AJK1PlayerCharacter>(It->Get()->GetPawn());
		if (nullptr != Player)
		{
			Player->Resurrection();
			Player->CreatureStat->SetCurrentHP(Player->CreatureStat->GetMaxHp());

			//레이드에 대한 보상 재화는 드롭 아이템을 주워서 팔게끔 기획
			break;
		}
	}
	
}
