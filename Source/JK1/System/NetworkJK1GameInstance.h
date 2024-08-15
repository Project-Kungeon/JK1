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
