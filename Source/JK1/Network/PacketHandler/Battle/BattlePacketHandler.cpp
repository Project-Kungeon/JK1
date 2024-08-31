#include "BattlePacketHandler.h"

bool BattlePacketHandler::Handle_S_Attack(PacketSessionRef& session, message::S_Attack& pkt)
{
	if ( auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()) )
	{
		GameInstance->HandleAttack(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_WarriorAttack(PacketSessionRef& session, skill::S_Warrior_Attack& pkt)
{

	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleWarriorAttack(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_WarriorE(PacketSessionRef& session, skill::S_Warrior_E& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleWarriorE(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_WarriorR(PacketSessionRef& session, skill::S_Warrior_R& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleWarriorR(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_AssassinAttack(PacketSessionRef& session, skill::S_ASSASSIN_Attack& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleAssassinAttack(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_AssassinQ(PacketSessionRef& session, skill::S_ASSASSIN_Q& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleAssassinQ(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_AssassinR(PacketSessionRef& session, skill::S_ASSASSIN_R& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleAssassinR(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_AssassinLS(PacketSessionRef& session, skill::S_ASSASSIN_LS& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleAssassinLS(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_AssassinLSOff(PacketSessionRef& session, skill::S_Assassin_LS_Off& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleAssassinLsOff(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_AssassinE(PacketSessionRef& session, skill::S_Assassin_E& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleAssassinE(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_ArchorAttack(PacketSessionRef& session, skill::S_Archor_Attack& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleArchorAttack(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_ArchorE(PacketSessionRef& session, skill::S_Archor_E& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleArchorE(pkt);
	}
	return true;
}
