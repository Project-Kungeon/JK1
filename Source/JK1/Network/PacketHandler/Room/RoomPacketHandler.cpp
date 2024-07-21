#include "RoomPacketHandler.h"

bool RoomPacketHandler::Handle_S_EnterRoom(PacketSessionRef& session, message::S_EnterRoom& pkt)
{
	if ( auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()) )
	{
		// TODO : 다른 플레이어의 폰을 소환
		GameInstance->HandleSpawn(pkt);
	}

	return true;
}

bool RoomPacketHandler::Handle_S_LeaveRoom(PacketSessionRef& session, message::S_LeaveRoom& pkt)
{
	if ( auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()) )
	{
		// TODO : 다른 플레이어의 방 퇴장 패킷을 처리
	}
	return true;
}

bool RoomPacketHandler::Handle_S_Spawn(PacketSessionRef& session, message::S_Spawn& pkt)
{
	if ( auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()) )
	{
		// TODO : 다른 오브젝트의 스폰 패킷을 처리
		GameInstance->HandleSpawn(pkt);
	}
	return true;
}

bool RoomPacketHandler::Handle_S_Despawn(PacketSessionRef& session, message::S_Despawn& pkt)
{
	if ( auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()) )
	{
		// TODO : 다른 플레이어의 디스폰 패킷을 처리
		//GameInstance->HandleDespawn(pkt);
	}
	return true;
}

bool RoomPacketHandler::Handle_S_Move(PacketSessionRef& session, message::S_Move& pkt)
{

	if ( auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()) )
	{
		// TODO : 다른 플레이어의 이동 패킷을 처리
		GameInstance->HandleMove(pkt);
	}
	return true;
}