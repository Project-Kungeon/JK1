#pragma once
#include "JK1.h"

class MonsterPatternPacketHandler
{
public:
	static bool Handle_S_Rampage_Roar(PacketSessionRef& session, monster::pattern::S_Rampage_Roar& pkt);
	static bool Handle_S_Rampage_EarthQuake(PacketSessionRef& session, monster::pattern::S_Rampage_EarthQuake& pkt);
	static bool Handle_S_TurnToTarget(PacketSessionRef& session, monster::pattern::S_TurnToTarget& pkt);
	static bool Handle_S_Rampage_BasicAttack(PacketSessionRef& session, monster::pattern::S_Rampage_BasicAttack& pkt);
	static bool Handle_S_Rampage_EnhancedAttack(PacketSessionRef& session, monster::pattern::S_Rampage_EnhanceAttack& pkt);
};