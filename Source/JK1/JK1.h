// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/buffer.hpp>
#include "Message.pb.h"
#include "Skill.pb.h"
#include "Item.pb.h"
#include "GameRound.pb.h"
#include "MonsterPattern.pb.h"
#include "Ping.pb.h"
#include "Packet.h"

class PacketSession;

using namespace boost;
using boost::asio::ip::tcp;
using boost::asio::ip::udp;

#define USING_SHARED_PTR(name)	using name##Ref = TSharedPtr<class name>;
USING_SHARED_PTR(PacketSession);

#include "Lobby/LobbyPacketHandler.h"
#include "Room/RoomPacketHandler.h"
#include "Battle/BattlePacketHandler.h"
#include "Battle/MonsterPatternPacketHandler.h"
#include "Interactive/InteractivePacketHandler.h"
#include "PingPong/PingPongPacketHandler.h"
#include "ClientPacketHandler.h"

#include "NetworkJK1GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#define SEND_PACKET(headerCode, pkt)															\
	const size_t requiredSize = PacketUtil::RequiredSize(pkt);									\
	char* rawBuffer = new char[requiredSize];													\
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);									\
	PacketUtil::Serialize(sendBuffer, headerCode, pkt);											\
	Cast<UNetworkJK1GameInstance>(GWorld->GetGameInstance())->SendPacket(sendBuffer);

#define UDP_SEND_PACKET(headerCode, pkt)															\
	const size_t requiredSize = PacketUtil::RequiredSize(pkt);									\
	char* rawBuffer = new char[requiredSize];													\
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);									\
	PacketUtil::Serialize(sendBuffer, headerCode, pkt);											\
	Cast<UNetworkJK1GameInstance>(GWorld->GetGameInstance())->UdpSendPacket(sendBuffer);

#define SEND_PACKET_V2(session, headerCode, pkt)												\
	const size_t requiredSize = PacketUtil::RequiredSize(pkt);									\
	char* rawBuffer = new char[requiredSize];													\
	auto sendBuffer = asio::buffer(rawBuffer, requiredSize);									\
	PacketUtil::Serialize(sendBuffer, message::HEADER::ENTER_ROOM_REQ, pkt);					\
	Cast<UNetworkJK1GameInstance>(session->GetGameInstance())->SendPacket(sendBuffer);