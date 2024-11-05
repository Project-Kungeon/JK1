#pragma once
#include "JK1.h"

class PingPongPacketHandler
{
public:
	static bool Handle_S_Pong(PacketSessionRef& session, ping::S_Pong&pkt);
};