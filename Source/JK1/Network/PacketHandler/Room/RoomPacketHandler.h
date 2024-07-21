 #pragma once
#include "JK1.h"
#include "NetworkJK1GameInstance.h"

class RoomPacketHandler
{
public:
	static bool Handle_S_EnterRoom(PacketSessionRef& session, message::S_EnterRoom& pkt);
	static bool Handle_S_LeaveRoom(PacketSessionRef& session, message::S_LeaveRoom& pkt);
	static bool Handle_S_Spawn(PacketSessionRef& session, message::S_Spawn& pkt);
	static bool Handle_S_Despawn(PacketSessionRef& session, message::S_Despawn& pkt);
	static bool Handle_S_Move(PacketSessionRef& session, message::S_Move& pkt);
};