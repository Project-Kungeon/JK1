// Copyright 2024 All Rights Reserved by J&K


#include "System/NetworkJK1GameInstance.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Controller/Player/JK1PlayerController.h"
#include "Creature/PC/Warrior/JK1Warrior.h"
#include "Creature/PC/Assassin/JK1Assassin.h"
#include "Creature/PC/Archor/JK1Archor.h"
#include "Creature/JK1CreatureStatComponent.h"

void UNetworkJK1GameInstance::Init()
{
	Super::Init();
}

void UNetworkJK1GameInstance::ConnectToGameServer()
{
	TSharedPtr<asio::io_context> io_contextRef = MakeShared<asio::io_context>();

	//_sock = new tcp::socket(io_context);
	//GameSession = MakeShared<PacketSession>(io_contextRef);

	asio::io_context* io_context = new asio::io_context;
	GameSession = MakeShared<PacketSession>(io_context);

	GameSession->Connect(std::string("127.0.0.1"), 4242);
	GameSession->Run();

	//message::C_Login Pkt;
	///SEND_PACKET(message::HEADER::LOGIN_REQ, Pkt);

	message::C_EnterRoom EnterRoomPkt;

	if (MyCharacterClass == "Warrior")
	{
		EnterRoomPkt.set_player_type(message::PLAYER_TYPE_WARRIOR);
	}
	else if (MyCharacterClass == "Archor")
	{
		EnterRoomPkt.set_player_type(message::PLAYER_TYPE_ARCHER);
	}
	else if (MyCharacterClass == "Assassin")
	{
		EnterRoomPkt.set_player_type(message::PLAYER_TYPE_ASSASSIN);
	}

	
	SEND_PACKET(message::HEADER::ENTER_ROOM_REQ, EnterRoomPkt);

	//GameSession->Run(io_contextRef);
}

void UNetworkJK1GameInstance::DisconnectFromGameServer()
{
	GameSession->GetIOContext().stop();
	//delete &(GameSession->GetIOContext());
	GameSession = nullptr;

}

void UNetworkJK1GameInstance::SendPacket(asio::mutable_buffer& buffer)
{
	GameSession->SendPacket(buffer);
}

void UNetworkJK1GameInstance::HandleSpawn(const message::ObjectInfo& info)
{
	// Empty
}

void UNetworkJK1GameInstance::HandleSpawn(const message::CreatureInfo& info)
{
	// Empty
}

void UNetworkJK1GameInstance::HandleSpawn(const message::PlayerInfo& info, bool isMyPlayer)
{
	// 세션이 죽은 상태라면 패스
	if (GameSession == nullptr)
		return;

	// 월드를 못 불러오면 패스
	auto* World = GetWorld();
	if (World == nullptr)
		return;

	const uint64 ObjectId = info.creature_info().object_info().object_id();

	// 스폰시키려는 플레이어가 이미 존재하면 패스
	if (Players.Find(ObjectId) != nullptr)
		return;

	// 스폰위치 설정(위치는 서버가 정해준다)
	FVector SpawnLocation(
		info.creature_info().object_info().pos_info().x(), 
		info.creature_info().object_info().pos_info().y(), 
		info.creature_info().object_info().pos_info().z());

	// 만약 내 플레이어라면, 필요한 컴포넌트를 달아준다.
	if (isMyPlayer)
	{
		AsyncTask(ENamedThreads::GameThread, [isMyPlayer, this, info, World, SpawnLocation]()
			{
				auto* PC = UGameplayStatics::GetPlayerController(this, 0);
				AJK1PlayerCharacter* Player;
				switch (info.player_type())
				{
				case message::PLAYER_TYPE_WARRIOR:
					Player = Cast<AJK1PlayerCharacter>(World->SpawnActor(WarriorClass, &SpawnLocation));
					break;
				case message::PLAYER_TYPE_ASSASSIN:
					Player = Cast<AJK1PlayerCharacter>(World->SpawnActor(AssassinClass, &SpawnLocation));
					break;
				case message::PLAYER_TYPE_ARCHER:
					Player = Cast<AJK1PlayerCharacter>(World->SpawnActor(ArchorClass, &SpawnLocation));
					break;
				default:
					Player = Cast<AJK1PlayerCharacter>(World->SpawnActor(OtherPlayerClass, &SpawnLocation));
					break;

				}
				if (Player == nullptr)
					return;
				//auto* Player = Cast<AJK1PlayerCharacter>(PC->GetPawn());
				
				PC->Possess(Player);
				Player->isMyPlayer = true;
				
				// TODO : 나중에 초기 정보 던져주도록 설정해야 함.
				Player->CreatureStat->SetCreatureInfo(info.creature_info());
				Player->SetPlayerInfo(info.creature_info().object_info().pos_info());

				MyPlayer = Player;
				Players.Add(info.creature_info().object_info().object_id(), Player);

				Cast<AJK1PlayerCharacter>(Player)->isConnected = true;
			});

	}
	else
	{
		AsyncTask(ENamedThreads::GameThread, [isMyPlayer, this, info, World, SpawnLocation]()
			{
				AJK1PlayerCharacter* Player;
				switch (info.player_type())
				{
				case message::PLAYER_TYPE_WARRIOR:
					Player = Cast<AJK1PlayerCharacter>(World->SpawnActor(WarriorClass, &SpawnLocation));
					break;
				case message::PLAYER_TYPE_ASSASSIN:
					Player = Cast<AJK1PlayerCharacter>(World->SpawnActor(AssassinClass, &SpawnLocation));
					break;
				case message::PLAYER_TYPE_ARCHER:
					Player = Cast<AJK1PlayerCharacter>(World->SpawnActor(ArchorClass, &SpawnLocation));
					break;
				default:
					Player = Cast<AJK1PlayerCharacter>(World->SpawnActor(OtherPlayerClass, &SpawnLocation));
					break;

				}
				Player->CreatureStat->SetCreatureInfo(info.creature_info());
				Player->SetPlayerInfo(info.creature_info().object_info().pos_info());

				Players.Add(info.creature_info().object_info().object_id(), Player);
			});
	}
}

// 내가 아닌 다른 개체가 스폰되었을 때 동기화해주는 함수
void UNetworkJK1GameInstance::HandleSpawn(message::S_Spawn& SpawnPkt)
{
	for (auto& player : SpawnPkt.players())
	{
		HandleSpawn(player, false);
	}
}

void UNetworkJK1GameInstance::HandleSpawn(message::S_EnterRoom& EnterRoomPkt)
{
	HandleSpawn(EnterRoomPkt.player_info(), true);
}

void UNetworkJK1GameInstance::HandleMove(const message::S_Move& movePkt)
{
	if (GameSession == nullptr)
		return;

	auto* World = GetWorld();
	if (World == nullptr)
		return;

	const uint64 objectId = movePkt.posinfo().object_id();
	AJK1PlayerCharacter** FindActor = Players.Find(objectId);
	if (FindActor == nullptr)
		return;

	AJK1PlayerCharacter* Player = (*FindActor);
	if (Player->isMyPlayer)
		return;

	const message::PosInfo& info = movePkt.posinfo();
	Player->SetDestInfo(info);

}

void UNetworkJK1GameInstance::HandleAttack(const message::S_Attack& attackPkt)
{
	const uint64 objectId = attackPkt.object_id();
	const float damage = attackPkt.damage();
	
	if (auto** FindAttacker = Players.Find(objectId))
	{
		for (auto& victimId : attackPkt.target_ids())
		{
			auto** FindActor = Players.Find(victimId);
			auto* Victim = (*FindActor);
			Victim->CreatureStat->HitDamage(damage, *FindAttacker);

			UE_LOG(LogTemp, Log, TEXT("%lld attacked by %lld Damage: %f"), victimId, objectId, damage);
		}
	}
}

void UNetworkJK1GameInstance::HandleDeath(const message::S_Death& deathPkt)
{
	const uint64 objectId = deathPkt.object_id();
	if (auto** DeadCreature = Players.Find(objectId))
	{
		auto* Dead = *(DeadCreature);
		UE_LOG(LogTemp, Log, TEXT("%d id creature dead"), objectId);
	}
}

void UNetworkJK1GameInstance::HandleWarriorAttack(const skill::S_Warrior_Attack& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		Attacker->Attack();
	}
	
}

void UNetworkJK1GameInstance::HandleWarriorE(const skill::S_Warrior_E& skillPkt)
{
	const uint64 objectId = skillPkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Warrior = Cast<AJK1Warrior>(Attacker);
		Warrior->WarriorE();
	}
}

void UNetworkJK1GameInstance::HandleWarriorR(const skill::S_Warrior_R& skillPkt)
{
	const uint64 objectId = skillPkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Warrior = Cast<AJK1Warrior>(Attacker);
		Warrior->WarriorR();
	}
}

void UNetworkJK1GameInstance::HandleAssassinAttack(const skill::S_ASSASSIN_Attack& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		Attacker->Attack();
	}
}

void UNetworkJK1GameInstance::HandleAssassinQ(const skill::S_ASSASSIN_Q& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Assassin = Cast<AJK1Assassin>(Attacker);
		FVector SpawnPoint(pkt.x(), pkt.y(), pkt.z());
		FRotator SpawnRotation(pkt.pitch(), pkt.yaw(), pkt.roll());

		Assassin->AssassinQ(SpawnPoint, SpawnRotation);
	}
}

void UNetworkJK1GameInstance::HandleAssassinR(const skill::S_ASSASSIN_R& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Assassin = Cast<AJK1Assassin>(Attacker);
		Assassin->AssassinR();
	}
}

void UNetworkJK1GameInstance::HandleAssassinLS(const skill::S_ASSASSIN_LS& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Assassin = Cast<AJK1Assassin>(Attacker);
		Assassin->AssassinLSOn();
	}
}

void UNetworkJK1GameInstance::HandleAssassinLsOff(const skill::S_Assassin_LS_Off& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Assassin = Cast<AJK1Assassin>(Attacker);
		Assassin->AssassinLSOff();
	}
}

void UNetworkJK1GameInstance::HandleAssassinE(const skill::S_Assassin_E& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Assassin = Cast<AJK1Assassin>(Attacker);

		FVector HitLocation(pkt.x(), pkt.y(), pkt.z());
		Assassin->AssassinE(HitLocation);
	}
}

void UNetworkJK1GameInstance::HandleArchorAttack(const skill::S_Archor_Attack& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Archor = Cast<AJK1Archor>(Attacker);
		FVector StartPoint(pkt.start_x(), pkt.start_y(), pkt.start_z());
		FVector EndPoint(pkt.end_x(), pkt.end_y(), pkt.end_z());
		Archor->ArchorAttack(StartPoint, EndPoint);
	}
}

void UNetworkJK1GameInstance::HandleArchorQ_Charging(const skill::S_Archor_Q_Charging& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Archor = Cast<AJK1Archor>(Attacker);
		Archor->ArchorQ_Charging();
	}
}

void UNetworkJK1GameInstance::HandleArchorQ_Shot(const skill::S_Archor_Q_Shot& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Archor = Cast<AJK1Archor>(Attacker);
		FVector StartPoint(pkt.start_x(), pkt.start_y(), pkt.start_z());
		FVector EndPoint(pkt.end_x(), pkt.end_y(), pkt.end_z());
		Archor->ArchorQ_Shot(StartPoint, EndPoint);
	}
}

void UNetworkJK1GameInstance::HandleArchorE(const skill::S_Archor_E& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Archor = Cast<AJK1Archor>(Attacker);
		FVector SkillPoint(pkt.x(), pkt.y(), pkt.z());
		Archor->ArchorE(SkillPoint);
	}
}

void UNetworkJK1GameInstance::HandleArchorR(const skill::S_Archor_R& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Archor = Cast<AJK1Archor>(Attacker);
		Archor->ArchorR();
	}
}

void UNetworkJK1GameInstance::HandleArchorR_Off(const skill::S_Archor_R_Off& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Archor = Cast<AJK1Archor>(Attacker);
		Archor->EndSkillR();
	}
}

void UNetworkJK1GameInstance::HandleArchorLS(const skill::S_Archor_LS& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Archor = Cast<AJK1Archor>(Attacker);
		Archor->ArchorLS();
	}
}

void UNetworkJK1GameInstance::HandleArchorLS_Off(const skill::S_Archor_LS_Off& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Archor = Cast<AJK1Archor>(Attacker);
		Archor->BIsLShift();
	}
}
