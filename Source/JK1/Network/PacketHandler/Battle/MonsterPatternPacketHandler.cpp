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
    if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
    {
        GameInstance->HandleRampageTurnToTarget(pkt);
    }
    return true;
}

bool MonsterPatternPacketHandler::Handle_S_Rampage_BasicAttack(PacketSessionRef& session, monster::pattern::S_Rampage_BasicAttack& pkt)
{
    if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
    {
        GameInstance->HandleRampageBasicAttack(pkt);
    }
    return true;
}

bool MonsterPatternPacketHandler::Handle_S_Rampage_EnhancedAttack(PacketSessionRef& session, monster::pattern::S_Rampage_EnhanceAttack& pkt)
{
    if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
    {
        GameInstance->HandleRampageEnhancedAttack(pkt);
    }
    return true;
}

bool MonsterPatternPacketHandler::Handle_S_Monster_Move(PacketSessionRef& session, message::S_Move& pkt)
{
    if (auto* GameInstance = Cast<UNetworkJK1GameInstance>(session->GetGameInstance()))
    {
        GameInstance->HandleMonsterMove(pkt);
    }
    return true;
}
