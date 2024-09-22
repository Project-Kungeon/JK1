#include "MonsterPatternPacketHandler.h"

bool MonsterPatternPacketHandler::Handle_S_Rampage_Roar(PacketSessionRef& session, monster::pattern::S_Rampage_Roar& pkt)
{
    if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
    {
        GameInstance->HandleRampageRoar(pkt);
    }
    return true;
}

bool MonsterPatternPacketHandler::Handle_S_Rampage_EarthQuake(PacketSessionRef& session, monster::pattern::S_Rampage_EarthQuake& pkt)
{
    return true;
}

bool MonsterPatternPacketHandler::Handle_S_TurnToTarget(PacketSessionRef& session, monster::pattern::S_TurnToTarget& pkt)
{
    return true;
}

bool MonsterPatternPacketHandler::Handle_S_BasicAttack(PacketSessionRef& session, monster::pattern::S_Rampage_BasicAttack& pkt)
{
    return true;
}
