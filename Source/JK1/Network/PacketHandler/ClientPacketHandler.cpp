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

}