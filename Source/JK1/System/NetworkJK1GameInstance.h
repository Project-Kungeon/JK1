// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "PacketSession.h"
#include "JK1.h"
#include "JK1GameInstance.h"
#include "NetworkJK1GameInstance.generated.h"

class AJK1PlayerCharacter;
class AJK1Warrior;
class AJK1Archor;
class AJK1Assassin;
/**
 * 
 */
UCLASS()
class JK1_API UNetworkJK1GameInstance : public UJK1GameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
		void ConnectToGameServer();

	UFUNCTION(BlueprintCallable)
		void DisconnectFromGameServer();

	void SendPacket(asio::mutable_buffer& buffer);

	// 플레이어 소환(내 플레이어일 경우, Controller 부착)
	void HandleSpawn(const message::ObjectInfo& info);
	void HandleSpawn(const message::CreatureInfo& info);
	void HandleSpawn(const message::PlayerInfo& info, bool isMyPlayer);
	// 서버로부터 스폰 요청이 들어올 경우
	void HandleSpawn(message::S_Spawn& SpawnPkt);
	// 게임 접속 후, 내 플레이어 스폰
	void HandleSpawn(message::S_EnterRoom& EnterRoomPkt);

	void HandleMove(const message::S_Move& movePkt);
	void HandleDespawn(const message::S_Despawn& despawnPkt);

	void HandleAttack(const message::S_Attack& attackPkt);

	void HandleWarriorAttack(const skill::S_Warrior_Attack& pkt);
	void HandleWarriorE(const skill::S_Warrior_E& skillPkt);
	void HandleWarriorR(const skill::S_Warrior_R& skillPkt);

	void HandleAssassinAttack(const skill::S_ASSASSIN_Attack& pkt);
	void HandleAssassinQ(const skill::S_ASSASSIN_Q& pkt);
	void HandleAssassinR(const skill::S_ASSASSIN_R& pkt);
	void HandleAssassinLS(const skill::S_ASSASSIN_LS& pkt);
	void HandleAssassinLsOff(const skill::S_Assassin_LS_Off& pkt);
	void HandleAssassinE(const skill::S_Assassin_E& pkt);

	void HandleArchorAttack(const skill::S_Archor_Attack& pkt);
	void HandleArchorQ_Charging(const skill::S_Archor_Q_Charging& pkt);
	void HandleArchorQ_Shot(const skill::S_Archor_Q_Shot& pkt);
	void HandleArchorE(const skill::S_Archor_E& pkt);
	void HandleArchorR(const skill::S_Archor_R& pkt);
	void HandleArchorR_Off(const skill::S_Archor_R_Off& pkt);
	void HandleArchorLS(const skill::S_Archor_LS& pkt);
	void HandleArchorLS_Off(const skill::S_Archor_LS_Off& pkt);

private:
	PacketSessionRef GameSession;

public:
	FString MyCharacterClass;

	UPROPERTY(EditAnywhere);
	TSubclassOf<AJK1PlayerCharacter> OtherPlayerClass;

	UPROPERTY(EditAnywhere);
	TSubclassOf<AJK1Warrior> WarriorClass;

	UPROPERTY(EditAnywhere);
	TSubclassOf<AJK1Archor> ArchorClass;

	UPROPERTY(EditAnywhere);
	TSubclassOf<AJK1Assassin> AssassinClass;
	
	TMap<uint64, AJK1PlayerCharacter*> Players;
	AJK1PlayerCharacter* MyPlayer;
};
