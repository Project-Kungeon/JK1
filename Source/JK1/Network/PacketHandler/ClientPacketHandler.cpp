#include "ClientPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
{
    return false;
}

void ClientPacketHandler::Init()
{
    for (int i = 0; i < UINT16_MAX; i++)
        GPacketHandler[i] = Handle_INVALID;

    GPacketHandler[message::HEADER::LOGIN_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Login Handle"));
        return HandlePacket<message::S_Login>(LobbyPacketHandler::Handle_S_Login, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ENTER_ROOM_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_EnterRoom Handle"));
        return HandlePacket<message::S_EnterRoom>(RoomPacketHandler::Handle_S_EnterRoom, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::PLAYER_SPAWN_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Spawn Handle"));
        return HandlePacket<message::S_Spawn>(RoomPacketHandler::Handle_S_Spawn, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::PLAYER_MOVE_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Move Handle"));
        return HandlePacket<message::S_Move>(RoomPacketHandler::Handle_S_Move, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::PLAYER_ATTACK_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Attack Handle"));
        return HandlePacket<message::S_Attack>(BattlePacketHandler::Handle_S_Attack, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::CREATURE_DEATH_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Death Handle"));
        return HandlePacket<message::S_Death>(BattlePacketHandler::Handle_S_Death, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::CREATURE_HEAL_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
        {
            UE_LOG(LogTemp, Log, TEXT("S_Heal Handle"));
            return HandlePacket<message::S_Heal>(BattlePacketHandler::Handle_S_Heal, session, buffer, header, offset);
        };
    GPacketHandler[message::HEADER::SESSION_PONG_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
        {
            UE_LOG(LogTemp, Log, TEXT("S_Pong Handle"));
            return HandlePacket<ping::S_Pong>(PingPongPacketHandler::Handle_S_Pong, session, buffer, header, offset);
        };

    GPacketHandler[message::HEADER::WARRIOR_ATTACK_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_WarriorAttack Handle"));
        return HandlePacket<skill::S_Warrior_Attack>(BattlePacketHandler::Handle_S_WarriorAttack, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::WARRIOR_Q_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
        {
            UE_LOG(LogTemp, Log, TEXT("S_WarriorQ Handle"));
            return HandlePacket<skill::S_Warrior_Q>(BattlePacketHandler::Handle_S_WarriorQ, session, buffer, header, offset);
        };
    GPacketHandler[message::HEADER::WARRIOR_Q_HIT_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
        {
            UE_LOG(LogTemp, Log, TEXT("S_WarriorQ_Hit Handle"));
            return HandlePacket<skill::S_Warrior_Q_Hit>(BattlePacketHandler::Handle_S_WarriorQ_Hit, session, buffer, header, offset);
        };
    GPacketHandler[message::HEADER::WARRIOR_E_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_WarriorE Handle"));
        return HandlePacket<skill::S_Warrior_E>(BattlePacketHandler::Handle_S_WarriorE, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::WARRIOR_E_SUCCESS_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
        {
            UE_LOG(LogTemp, Log, TEXT("S_WarriorE_Success Handle"));
            return HandlePacket<skill::S_Warrior_E_Success>(BattlePacketHandler::Handle_S_WarriorE_Success, session, buffer, header, offset);
        };
    GPacketHandler[message::HEADER::WARRIOR_R_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_WarriorR Handle"));
        return HandlePacket<skill::S_Warrior_R>(BattlePacketHandler::Handle_S_WarriorR, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::WARRIOR_LS_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_WarriorLS Handle"));
        return HandlePacket<skill::S_Warrior_LS>(BattlePacketHandler::Handle_S_WarriorLS, session, buffer, header, offset);
    };

    // Assassin
    GPacketHandler[message::HEADER::ASSASSIN_ATTACK_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_AssassinAttack Handle"));
        return HandlePacket<skill::S_ASSASSIN_Attack>(BattlePacketHandler::Handle_S_AssassinAttack, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ASSASSIN_Q_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_AssassinQ Handle"));
        return HandlePacket<skill::S_ASSASSIN_Q>(BattlePacketHandler::Handle_S_AssassinQ, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ASSASSIN_R_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_AssassinR Handle"));
        return HandlePacket<skill::S_ASSASSIN_R>(BattlePacketHandler::Handle_S_AssassinR, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ASSASSIN_LS_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_AssassinLS Handle"));
        return HandlePacket<skill::S_ASSASSIN_LS>(BattlePacketHandler::Handle_S_AssassinLS, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ASSASSIN_LS_OFF_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_AssassinLSOff Handle"));
        return HandlePacket<skill::S_Assassin_LS_Off>(BattlePacketHandler::Handle_S_AssassinLSOff, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ASSASSIN_E_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_AssassinE Handle"));
        return HandlePacket<skill::S_Assassin_E>(BattlePacketHandler::Handle_S_AssassinE, session, buffer, header, offset);
    };

    // Archor
    GPacketHandler[message::HEADER::ARCHOR_ATTACK_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_ArchorAttack Handle"));
        return HandlePacket<skill::S_Archor_Attack>(BattlePacketHandler::Handle_S_ArchorAttack, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ARCHOR_Q_CHARGING_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_ArchorQ_Charging Handle"));
        return HandlePacket<skill::S_Archor_Q_Charging>(BattlePacketHandler::Handle_S_ArchorQ_Charging, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ARCHOR_Q_SHOT_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_ArchorQ_Shot Handle"));
        return HandlePacket<skill::S_Archor_Q_Shot>(BattlePacketHandler::Handle_S_ArchorQ_Shot, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ARCHOR_E_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_ArchorE Handle"));
        return HandlePacket<skill::S_Archor_E>(BattlePacketHandler::Handle_S_ArchorE, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ARCHOR_R_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_ArchorR Handle"));
        return HandlePacket<skill::S_Archor_R>(BattlePacketHandler::Handle_S_ArchorR, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ARCHOR_R_OFF_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_ArchorR_Off Handle"));
        return HandlePacket<skill::S_Archor_R_Off>(BattlePacketHandler::Handle_S_ArchorR_Off, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ARCHOR_LS_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_ArchorLS Handle"));
        return HandlePacket<skill::S_Archor_LS>(BattlePacketHandler::Handle_S_ArchorLS, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::ARCHOR_LS_OFF_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_ArchorR_Off Handle"));
        return HandlePacket<skill::S_Archor_LS_Off>(BattlePacketHandler::Handle_S_ArchorLS_Off, session, buffer, header, offset);
    };

    // Monster Pattern : Rampage
    GPacketHandler[message::HEADER::RAMPAGE_ROAR_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Rampage_Roar Handle"));
        return HandlePacket<monster::pattern::S_Rampage_Roar>(MonsterPatternPacketHandler::Handle_S_Rampage_Roar, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::RAMPAGE_BASICATTACK_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Rampage_BasicAttack Handle"));
        return HandlePacket<monster::pattern::S_Rampage_BasicAttack>(MonsterPatternPacketHandler::Handle_S_Rampage_BasicAttack, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::RAMPAGE_TURNTOTARGET_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Rampage_TurnToTarget Handle"));
        return HandlePacket<monster::pattern::S_TurnToTarget>(MonsterPatternPacketHandler::Handle_S_TurnToTarget, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::RAMPAGE_ENHANCEDATTACK_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Rampage_EnhancedAttack Handle"));
        return HandlePacket<monster::pattern::S_Rampage_EnhanceAttack>(MonsterPatternPacketHandler::Handle_S_Rampage_EnhancedAttack, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::MONSTER_MOVE_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_Monster_Move Handle"));
        return HandlePacket<message::S_Move>(MonsterPatternPacketHandler::Handle_S_Monster_Move, session, buffer, header, offset);
    };

    GPacketHandler[message::HEADER::ITEM_PICKED_UP_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
        {
            UE_LOG(LogTemp, Log, TEXT("S_Item_PickedUp Handle"));
            return HandlePacket<game::item::S_Item_PickedUp>(InteractivePacketHandler::Handle_S_Item_PickedUp, session, buffer, header, offset);
        };
    GPacketHandler[message::HEADER::ITEM_CONSUMEABLE_USED_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
        {
            UE_LOG(LogTemp, Log, TEXT("S_Item_ConsumeableUsed Handle"));
            return HandlePacket<game::item::S_Item_ConsumeableUsed>(InteractivePacketHandler::Handle_S_Item_ConsumeableUsed, session, buffer, header, offset);
        };
    GPacketHandler[message::HEADER::ITEM_ACQUISITION_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
        {
            UE_LOG(LogTemp, Log, TEXT("S_Item_Acquisition Handle"));
            return HandlePacket<game::item::S_Item_Acquisition>(InteractivePacketHandler::Handle_S_Item_Acquisition, session, buffer, header, offset);
        };
    GPacketHandler[message::HEADER::ITEM_OPENINVENTORY] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
        {
            UE_LOG(LogTemp, Log, TEXT("S_Item_OpenInventory Handle"));
            return HandlePacket<game::item::S_Item_OpenInventory>(InteractivePacketHandler::Handle_S_Item_OpenInventory, session, buffer, header, offset);
        };




}