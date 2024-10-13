#include "InteractivePacketHandler.h"

bool InteractivePacketHandler::Handle_S_Item_PickedUp(PacketSessionRef& session, game::item::S_Item_PickedUp& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleItemPickedUp(pkt);
	}
	return true;
}

bool InteractivePacketHandler::Handle_S_Item_ConsumeableUsed(PacketSessionRef& session, game::item::S_Item_ConsumeableUsed& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleItemConsumeableUsed(pkt);
	}
	return true;
}

bool InteractivePacketHandler::Handle_S_Item_Acquisition(PacketSessionRef& session, game::item::S_Item_Acquisition& pkt)
{
	if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
	{
		GameInstance->HandleItemAcquisition(pkt);
	}
	return true;
}
