#pragma once
#include "JK1.h"

class BattlePacketHandler
{
public:
	static bool Handle_S_Attack(PacketSessionRef& session, message::S_Attack& pkt);

	static bool Handle_S_WarriorAttack(PacketSessionRef& session, skill::S_Warrior_Attack& pkt);
	static bool Handle_S_WarriorE(PacketSessionRef& session, skill::S_Warrior_E& pkt);
	static bool Handle_S_WarriorR(PacketSessionRef& session, skill::S_Warrior_R& pkt);

	static bool Handle_S_AssassinAttack(PacketSessionRef& session, skill::S_ASSASSIN_Attack& pkt);
	static bool Handle_S_AssassinQ(PacketSessionRef& session, skill::S_ASSASSIN_Q& pkt);
	static bool Handle_S_AssassinR(PacketSessionRef& session, skill::S_ASSASSIN_R& pkt);
	static bool Handle_S_AssassinLS(PacketSessionRef& session, skill::S_ASSASSIN_LS& pkt);
};