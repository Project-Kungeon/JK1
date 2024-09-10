#pragma once
#include "JK1.h"

class BattlePacketHandler
{
public:
	static bool Handle_S_Attack(PacketSessionRef& session, message::S_Attack& pkt);
	static bool Handle_S_Death(PacketSessionRef& session, message::S_Death& pkt);

	static bool Handle_S_WarriorAttack(PacketSessionRef& session, skill::S_Warrior_Attack& pkt);
	static bool Handle_S_WarriorE(PacketSessionRef& session, skill::S_Warrior_E& pkt);
	static bool Handle_S_WarriorR(PacketSessionRef& session, skill::S_Warrior_R& pkt);

	static bool Handle_S_AssassinAttack(PacketSessionRef& session, skill::S_ASSASSIN_Attack& pkt);
	static bool Handle_S_AssassinQ(PacketSessionRef& session, skill::S_ASSASSIN_Q& pkt);
	static bool Handle_S_AssassinR(PacketSessionRef& session, skill::S_ASSASSIN_R& pkt);
	static bool Handle_S_AssassinLS(PacketSessionRef& session, skill::S_ASSASSIN_LS& pkt);
	static bool Handle_S_AssassinLSOff(PacketSessionRef& session, skill::S_Assassin_LS_Off& pkt);
	static bool Handle_S_AssassinE(PacketSessionRef& session, skill::S_Assassin_E& pkt);

	static bool Handle_S_ArchorAttack(PacketSessionRef& session, skill::S_Archor_Attack& pkt);
	static bool Handle_S_ArchorQ_Charging(PacketSessionRef& session, skill::S_Archor_Q_Charging& pkt);
	static bool Handle_S_ArchorQ_Shot(PacketSessionRef& session, skill::S_Archor_Q_Shot& pkt);
	static bool Handle_S_ArchorE(PacketSessionRef& session, skill::S_Archor_E& pkt);
	static bool Handle_S_ArchorR(PacketSessionRef& session, skill::S_Archor_R& pkt);
	static bool Handle_S_ArchorR_Off(PacketSessionRef& session, skill::S_Archor_R_Off& pkt);
	static bool Handle_S_ArchorLS(PacketSessionRef& session, skill::S_Archor_LS& pkt);
	static bool Handle_S_ArchorLS_Off(PacketSessionRef& session, skill::S_Archor_LS_Off& pkt);
};