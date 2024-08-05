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

bool BattlePacketHandler::Handle_S_WarriorAttack(PacketSessionRef& session, skill::S_Warrior_Attack& pkt)
{

	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		// TODO : 다른 오브젝트의 스폰 패킷을 처리
		GameInstance->HandleWarriorAttack(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_WarriorE(PacketSessionRef& session, skill::S_Warrior_E& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		// TODO : 다른 오브젝트의 스폰 패킷을 처리
		GameInstance->HandleWarriorE(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_WarriorR(PacketSessionRef& session, skill::S_Warrior_R& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		// TODO : 다른 오브젝트의 스폰 패킷을 처리
		GameInstance->HandleWarriorR(pkt);
	}
	return true;
}
