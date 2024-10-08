#include "LobbyPacketHandler.h"

bool LobbyPacketHandler::Handle_S_Login(PacketSessionRef& session, message::S_Login& pkt)
{

    for ( int32 i = 0; i < pkt.players_size(); i++ )
    {
        // TODO 모든 플레이어에 대해 전처리
        const message::ObjectInfo& Player = pkt.players(i);
    }

    // 방 입장 요청
    message::C_EnterRoom EnterRoomPkt;

    // TODO : 임시용으로 워리어만
    // 로비 맵 만들어지면 이곳을 동적으로!
    
    EnterRoomPkt.set_player_type(message::PLAYER_TYPE_WARRIOR);

 /*   const size_t requiredSize = PacketUtil::RequiredSize(pkt);									
    char* rawBuffer = new char[requiredSize];													
    auto sendBuffer = asio::buffer(rawBuffer, requiredSize);									
    PacketUtil::Serialize(sendBuffer, message::HEADEb R::ENTER_ROOM_REQ, pkt);

    session.ToSharedRef().Get().SendPacket(sendBuffer);*/
    SEND_PACKET_V2(session, message::HEADER::ENTER_ROOM_REQ, EnterRoomPkt);
    //SEND_PACKET(message::HEADER::ENTER_ROOM_REQ, EnterRoomPkt);
    return true;
}