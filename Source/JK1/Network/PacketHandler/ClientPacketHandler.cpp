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
    GPacketHandler[message::HEADER::WARRIOR_ATTACK_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_WarriorAttack Handle"));
        return HandlePacket<skill::S_Warrior_Attack>(BattlePacketHandler::Handle_S_WarriorAttack, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::WARRIOR_E_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_WarriorE Handle"));
        return HandlePacket<skill::S_Warrior_E>(BattlePacketHandler::Handle_S_WarriorE, session, buffer, header, offset);
    };
    GPacketHandler[message::HEADER::WARRIOR_R_RES] = [](PacketSessionRef& session, asio::mutable_buffer& buffer, PacketHeader& header, int& offset)
    {
        UE_LOG(LogTemp, Log, TEXT("S_WarriorR Handle"));
        return HandlePacket<skill::S_Warrior_R>(BattlePacketHandler::Handle_S_WarriorR, session, buffer, header, offset);
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

}