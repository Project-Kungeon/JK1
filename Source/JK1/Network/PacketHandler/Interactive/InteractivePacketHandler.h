#pragma once
#include "JK1.h"

class InteractivePacketHandler
{
public:
	static bool Handle_S_Item_PickedUp(PacketSessionRef& session, game::item::S_Item_PickedUp& pkt);
	static bool Handle_S_Item_ConsumeableUsed(PacketSessionRef& session, game::item::S_Item_ConsumeableUsed& pkt);
	static bool Handle_S_Item_Acquisition(PacketSessionRef& session, game::item::S_Item_Acquisition& pkt);
};

