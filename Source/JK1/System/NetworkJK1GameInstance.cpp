// Copyright 2024 All Rights Reserved by J&K


#include "System/NetworkJK1GameInstance.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Controller/Player/JK1PlayerController.h"
#include "Creature/PC/Warrior/JK1Warrior.h"
#include "Creature/PC/Assassin/JK1Assassin.h"
#include "Creature/PC/Archor/JK1Archor.h"
#include "Creature/Monster/Boss/JK1Rampage.h"
#include "Item/JK1ItemInstance.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Item/JK1InventorySubsystem.h"
#include "Subsystems/SubsystemBlueprintLibrary.h"

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

	GameSession->Connect(std::string("175.118.64.119"), 4242);
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

	FPlatformProcess::Sleep(1.0f);
	SEND_PACKET(message::HEADER::ENTER_ROOM_REQ, EnterRoomPkt);
	StartPingPacketTimer();
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

	if (GameSession.IsValid())
	{
		GameSession->SendPacket(buffer);
	}
	else
	{
		UE_LOG(LogSystem, Error, TEXT("GameSession is not valid!!"));
	}
}

void UNetworkJK1GameInstance::UdpSendPacket(asio::mutable_buffer& buffer)
{
	if (GameSession.IsValid())
	{
		GameSession->UdpSendPacket(buffer);
	}
	else
	{
		UE_LOG(LogSystem, Error, TEXT("GameSession is not valid!!"));
	}
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
				if (auto* jkPlayerController = Cast<AJK1PlayerController>(PC))
				{
					jkPlayerController->UpdateControlledCharacter();
					jkPlayerController->UpdateWidget();
				}
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

void UNetworkJK1GameInstance::HandleSpawn(const message::MonsterInfo& info)
{
	// 월드를 못 불러오면 패스
	auto* World = GetWorld();
	if (World == nullptr)
		return;

	const uint64 ObjectId = info.creature_info().object_info().object_id();

	// 스폰시키려는 플레이어가 이미 존재하면 패스
	if (Creatures.Find(ObjectId) != nullptr)
		return;

	// 스폰위치 설정(위치는 서버가 정해준다)
	FVector SpawnLocation(
		info.creature_info().object_info().pos_info().x(),
		info.creature_info().object_info().pos_info().y(),
		info.creature_info().object_info().pos_info().z());

	AsyncTask(ENamedThreads::GameThread, [this, info, World, SpawnLocation]()
		{
			AJK1MonsterBase* monster;
			switch (info.monster_type())
			{
			case message::MONSTER_TYPE_RAMPAGE:
				monster = Cast<AJK1MonsterBase>(World->SpawnActor(RampageClass, &SpawnLocation));
				break;
			default:
				monster = Cast<AJK1MonsterBase>(World->SpawnActor(OtherMonsterClass, &SpawnLocation));
				break;
			}
			if (monster != nullptr)
			{
				monster->CreatureStat->SetCreatureInfo(info.creature_info());
				Creatures.Add(info.creature_info().object_info().object_id(), monster);
			}
		});
}

void UNetworkJK1GameInstance::HandleSpawn(const message::ItemObjectInfo& info)
{
	// 월드를 못 불러오면 패스
	auto* World = GetWorld();
	if (World == nullptr)
		return;

	const uint64 ObjectId = info.object_info().object_id();

	// 스폰시키려는 플레이어가 이미 존재하면 패스
	if (Players.Find(ObjectId) != nullptr)
		return;

	// 스폰위치 설정(위치는 서버가 정해준다)
	FVector SpawnLocation(
		info.object_info().pos_info().x(),
		info.object_info().pos_info().y(),
		info.object_info().pos_info().z());

	AsyncTask(ENamedThreads::GameThread, [this, info, World, SpawnLocation]()
		{
			AJK1ItemInstance* itemInstance;
			switch (info.item_type())
			{
			case message::ItemType::Consumable:
				itemInstance = Cast<AJK1ItemInstance>(World->SpawnActor(ConsumeableItemClass, &SpawnLocation));
				break;
			default:
				itemInstance = Cast<AJK1ItemInstance>(World->SpawnActor(OtherItemClass, &SpawnLocation));
				break;
			}
			if (itemInstance != nullptr)
			{
				//itemInstance->CreatureStat->SetCreatureInfo(info.creature_info());
				itemInstance->Init(info);
				Items.Add(info.object_info().object_id(), itemInstance);
			}
		});
}

// 내가 아닌 다른 개체가 스폰되었을 때 동기화해주는 함수
void UNetworkJK1GameInstance::HandleSpawn(message::S_Spawn& SpawnPkt)
{
	for (auto& player : SpawnPkt.players())
	{
		HandleSpawn(player, false);
	}
	for (auto& monster : SpawnPkt.monsters())
	{
		HandleSpawn(monster);
	}
	for (auto& itemObject : SpawnPkt.itemobjects())
	{
		HandleSpawn(itemObject);
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
	// TEST를 위해 비활성화(2024.10.28)
	if (Player->isMyPlayer)
		return;
	if (objectId == 3)
	{
		cout << "dsadsa";
	}

	const message::PosInfo& info = movePkt.posinfo();
	Player->SetDestInfo(info);
	Player->SetMoveInfo(movePkt);

}

void UNetworkJK1GameInstance::HandleAttack(const message::S_Attack& attackPkt)
{
	const uint64 objectId = attackPkt.object_id();
	const float damage = attackPkt.damage();
	
	if (auto** FindAttacker = Players.Find(objectId))
	{
		for (auto& victimId : attackPkt.target_ids())
		{
			AJK1CreatureBase* Victim = nullptr;
			if (auto** player_pointer = Players.Find(victimId))
			{
				Victim = (*player_pointer);
			}
			else if (auto** creature_pointer = Creatures.Find(victimId))
			{
				Victim = (*creature_pointer);
			}
			if (Victim) Victim->CreatureStat->HitDamage(damage, *FindAttacker);
			

			UE_LOG(LogTemp, Log, TEXT("%lld attacked by %lld Damage: %f"), victimId, objectId, damage);
		}
	}

	if (auto** FindAttacker = Creatures.Find(objectId))
	{
		for (auto& victimId : attackPkt.target_ids())
		{
			AJK1CreatureBase* Victim = nullptr;
			if (auto** player_pointer = Players.Find(victimId))
			{
				Victim = (*player_pointer);
			}
			else if (auto** creature_pointer = Creatures.Find(victimId))
			{
				Victim = (*creature_pointer);
			}
			if (Victim) Victim->CreatureStat->HitDamage(damage, *FindAttacker);


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
		Dead->Death();
		UE_LOG(LogTemp, Log, TEXT("%d id creature dead"), objectId);
	}
}

void UNetworkJK1GameInstance::HandleHeal(const message::S_Heal& pkt)
{
	for (auto object_id : pkt.object_id())
	{
		if (auto** FindPlayer = Players.Find(object_id))
		{
			auto* creature = *(FindPlayer);
			creature->CreatureStat->SetCurrentHP(creature->CreatureStat->GetHP() + pkt.heal());
		}
		else if (auto** FindCreature = Creatures.Find(object_id))
		{
			auto* creature = *(FindCreature);
			creature->CreatureStat->SetCurrentHP(creature->CreatureStat->GetHP() + pkt.heal());
		}
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

void UNetworkJK1GameInstance::HandleWarriorQ(const skill::S_Warrior_Q& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Warrior = Cast<AJK1Warrior>(Attacker);
		Warrior->WarriorQ();
	}
}

void UNetworkJK1GameInstance::HandleWarriorQ_Hit(const skill::S_Warrior_Q_Hit& pkt)
{
	const uint64 objectId = pkt.object_id();
	const uint64 victimId = pkt.target_id();
	const float damage = pkt.damage();

	if (auto** FindAttacker = Players.Find(objectId))
	{
		AJK1CreatureBase* Victim = nullptr;
		if (auto** player_pointer = Players.Find(victimId))
		{
			Victim = (*player_pointer);
		}
		else if (auto** creature_pointer = Creatures.Find(victimId))
		{
			Victim = (*creature_pointer);
		}
		if (Victim) Victim->CreatureStat->HitDamage(damage, *FindAttacker);


		UE_LOG(LogTemp, Log, TEXT("%lld parried by %lld Damage: %f"), victimId, objectId, damage);
		
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

void UNetworkJK1GameInstance::HandleWarriorE_Success(const skill::S_Warrior_E_Success& skillPkt)
{
	const uint64 objectId = skillPkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Warrior = Cast<AJK1Warrior>(Attacker);
		Warrior->WarriorE_Success();
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

void UNetworkJK1GameInstance::HandleWarriorLS(const skill::S_Warrior_LS& skillPkt)
{
	const uint64 objectId = skillPkt.object_id();
	if (auto** FindAttacker = Players.Find(objectId))
	{
		auto* Attacker = *(FindAttacker);
		auto* Warrior = Cast<AJK1Warrior>(Attacker);
		FVector ForwardDirection(skillPkt.x(), skillPkt.y(), skillPkt.z());
		Warrior->WarriorLShift(ForwardDirection);
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

void UNetworkJK1GameInstance::HandleRampageRoar(const monster::pattern::S_Rampage_Roar& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindRampage = Creatures.Find(objectId))
	{
		auto* rampage = Cast<AJK1Rampage>(*(FindRampage));
		if (rampage != nullptr)
		{
			rampage->Roar();
		}

	}
}

void UNetworkJK1GameInstance::HandleRampageBasicAttack(const monster::pattern::S_Rampage_BasicAttack& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindRampage = Creatures.Find(objectId))
	{
		auto* rampage = Cast<AJK1Rampage>(*(FindRampage));
		if (rampage != nullptr)
		{
			rampage->BasicAttack();
		}

	}
}

void UNetworkJK1GameInstance::HandleRampageTurnToTarget(const monster::pattern::S_TurnToTarget& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindRampage = Creatures.Find(objectId))
	{
		auto* rampage = Cast<AJK1Rampage>(*(FindRampage));
		if (rampage != nullptr)
		{
			AsyncTask(ENamedThreads::GameThread, [this, pkt, rampage]()
				{
					FRotator rotator(pkt.pitch(), pkt.yaw(), pkt.roll());
					rampage->SetActorRotation(rotator);
				});
			
		}

	}
}

void UNetworkJK1GameInstance::HandleRampageEnhancedAttack(const monster::pattern::S_Rampage_EnhanceAttack& pkt)
{
	const uint64 objectId = pkt.object_id();
	if (auto** FindRampage = Creatures.Find(objectId))
	{
		auto* rampage = Cast<AJK1Rampage>(*(FindRampage));
		if (rampage != nullptr)
		{
			rampage->EnhancedAttack();
		}
	}
}

void UNetworkJK1GameInstance::HandleMonsterMove(const message::S_Move& pkt)
{
	if (GameSession == nullptr)
		return;

	auto* World = GetWorld();
	if (World == nullptr)
		return;

	const uint64 objectId = pkt.posinfo().object_id();
	AJK1CreatureBase** FindActor = Creatures.Find(objectId);
	if (FindActor == nullptr)
		return;

	AJK1CreatureBase* Creature = (*FindActor);

	const message::PosInfo& info = pkt.posinfo();

	if (info.state() == message::MOVE_STATE_RUN)	// 뛰는 중이라면
	{
		if (auto* Controller = Cast<AAIController>(Creature->GetController()))
		{
			FVector Dest(info.x(), info.y(), info.z());
			

			EPathFollowingRequestResult::Type Result = Controller->MoveToLocation(Dest);

			switch (Result)
			{
			case EPathFollowingRequestResult::Failed:
				UE_LOG(LogTemp, Warning, TEXT("MoveToLocation Failed"));
				break;
			case EPathFollowingRequestResult::AlreadyAtGoal:
				UE_LOG(LogTemp, Warning, TEXT("Already At Goal"));
				break;
			case EPathFollowingRequestResult::RequestSuccessful:
				UE_LOG(LogTemp, Warning, TEXT("Request Successful"));
				break;
			}
		}


		// 현재 좌표와 서버로부터 받아오는 좌표를 받아와서, 방향 벡터 계산
		//FVector CurrentLocation = Creature->GetActorLocation();
		//FVector TargetLocation(info.x(), info.y(), info.z());
		//FVector DirectionVector = TargetLocation - CurrentLocation;

		//// 정규화
		//DirectionVector.Normalize();

		//Creature->AddMovementInput(DirectionVector);
		//FRotator NewRotation = DirectionVector.Rotation();
		//Creature->SetActorRotation(NewRotation);
		//FVector vec(DestInfo->x(), DestInfo->y(), DestInfo->z());
		//SetActorLocation(vec);

	}
	else if (info.state() == message::MOVE_STATE_IDLE)
	{

		const FRotator YawRotation(0, info.yaw(), 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		Creature->AddMovementInput(ForwardDirection, 0);
		Creature->AddMovementInput(RightDirection, 0);
	}
}

void UNetworkJK1GameInstance::HandleItemPickedUp(const game::item::S_Item_PickedUp& pkt)
{
	if (GameSession == nullptr)
		return;

	auto* World = GetWorld();
	if (World == nullptr)
		return;

	const uint64 itemObjectId = pkt.picked_object_id();
	const uint64 playerId = pkt.player_id();

	if (Items.Find(itemObjectId) != nullptr)
	{
		AsyncTask(ENamedThreads::GameThread, [this, itemObjectId]()
			{
				Items[itemObjectId]->Destroy();
				Items.Remove(itemObjectId);
			});
		
	}
}

void UNetworkJK1GameInstance::HandleItemConsumeableUsed(const game::item::S_Item_ConsumeableUsed& pkt)
{
	// TODO : 인벤토리 내 아이템 개수 감소시켜야 한다.


}

void UNetworkJK1GameInstance::HandleItemAcquisition(const game::item::S_Item_Acquisition& pkt)
{
	UE_LOG(LogTemp, Log, TEXT("Item Get! %f"));
}

void UNetworkJK1GameInstance::HandleItemOpenInventory(const game::item::S_Item_OpenInventory& pkt)
{
	// TOOD : 인벤토리 열고, 결과 위젯 띄워야 함.
	UJK1InventorySubsystem* Inventory = Cast<UJK1InventorySubsystem>(USubsystemBlueprintLibrary::GetWorldSubsystem(this, UJK1InventorySubsystem::StaticClass()));
	if (Inventory)
	{
		Inventory->UpdateInventory(MyPlayer, pkt);
	}

}

void UNetworkJK1GameInstance::StartPingPacketTimer()
{
	// 1초마다 패킷 전송 (원하는 시간 간격으로 수정 가능)
	GetWorld()->GetTimerManager().SetTimer(PingPacketTimerHandle,
		this,
		&UNetworkJK1GameInstance::SendPingPacket,
		1.0f,
		true);
}

void UNetworkJK1GameInstance::StopPingPacketTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(PingPacketTimerHandle);
}

void UNetworkJK1GameInstance::SendPingPacket()
{
	ping::C_Ping pkt;
	pkt.set_client_send_time(GetSystemTimestamoMillisec());
	pkt.set_sequence_number(ping_sequence_number++);

	SEND_PACKET(message::SESSION_PING_REQ, pkt);
}

void UNetworkJK1GameInstance::HandlePongPacket(const ping::S_Pong& pkt)
{
	ping::C_CompletePing CompletePingPkt;
	CompletePingPkt.set_client_receive_time(GetSystemTimestamoMillisec());
	CompletePingPkt.set_client_send_time(pkt.client_send_time());
	CompletePingPkt.set_sequence_number(pkt.sequence_number());
	CompletePingPkt.set_server_send_time(pkt.server_send_time());
	CompletePingPkt.set_server_receive_time(pkt.server_receive_time());

	const size_t requiredSize = PacketUtil::RequiredSize(CompletePingPkt);
	char* rawBuffer = new char[requiredSize];
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);
	PacketUtil::Serialize(sendBuffer, message::HEADER::SESSION_COMPLETE_PING_RES, CompletePingPkt);
	UGameInstance* instance = GetWorld()->GetGameInstance();
	Cast<UNetworkJK1GameInstance>(instance)->SendPacket(sendBuffer);
}

uint64 UNetworkJK1GameInstance::GetSystemTimestamoMillisec()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
}
