#include "BattlePacketHandler.h"

bool BattlePacketHandler::Handle_S_Attack(PacketSessionRef& session, message::S_Attack& pkt)
{
	if ( auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()) )
	{
		// TODO : 다른 오브젝트의 스폰 패킷을 처리
		GameInstance->HandleAttack(pkt);
	}
	return true;
}
