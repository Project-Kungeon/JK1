#include "BattlePacketHandler.h"

bool BattlePacketHandler::Handle_S_Attack(PacketSessionRef& session, message::S_Attack& pkt)
{
	if ( auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()) )
	{
		GameInstance->HandleAttack(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_Death(PacketSessionRef& session, message::S_Death& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleDeath(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_Heal(PacketSessionRef& session, message::S_Heal& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleHeal(pkt);
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

bool BattlePacketHandler::Handle_S_WarriorLS(PacketSessionRef& session, skill::S_Warrior_LS& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleWarriorLS(pkt);
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

bool BattlePacketHandler::Handle_S_ArchorQ_Charging(PacketSessionRef& session, skill::S_Archor_Q_Charging& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleArchorQ_Charging(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_ArchorQ_Shot(PacketSessionRef& session, skill::S_Archor_Q_Shot& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleArchorQ_Shot(pkt);
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

bool BattlePacketHandler::Handle_S_ArchorR(PacketSessionRef& session, skill::S_Archor_R& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleArchorR(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_ArchorR_Off(PacketSessionRef& session, skill::S_Archor_R_Off& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleArchorR_Off(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_ArchorLS(PacketSessionRef& session, skill::S_Archor_LS& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleArchorLS(pkt);
	}
	return true;
}

bool BattlePacketHandler::Handle_S_ArchorLS_Off(PacketSessionRef& session, skill::S_Archor_LS_Off& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleArchorLS_Off(pkt);
	}
	return true;
}
