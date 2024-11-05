#include "PingPongPacketHandler.h"

bool PingPongPacketHandler::Handle_S_Pong(PacketSessionRef& session, ping::S_Pong& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandlePongPacket(pkt);
	}
	return true;
}
