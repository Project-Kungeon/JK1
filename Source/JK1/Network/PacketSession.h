// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "JK1.h"
#include "CoreMinimal.h"

/**
 * 
 */
class JK1_API PacketSession : public TSharedFromThis<PacketSession>
{
public:
	PacketSession() : _socket(nullptr), _udp_socket(nullptr) {}

	PacketSession(asio::io_context* io_context);

	//PacketSession(TWeakPtr<asio::io_context> io_context);

	~PacketSession();


	void Run();
	void Run(TSharedPtr<asio::io_context> io_context);

	void Connect(std::string host, int port);


	void SendPacket(asio::mutable_buffer& buffer)
	{
		AsyncWrite(buffer);
	}
	void UdpSendPacket(asio::mutable_buffer& buffer)
	{
		AsyncUdpWrite(buffer);
	}

	// 비동기 읽기 호출
	void AsyncRead();
	void AsyncUdpRead();

	UGameInstance* GetGameInstance() { return GameInstance; }

	asio::io_context& GetIOContext() { return *_io_context; }


private:
	// 비동기 쓰기 호출
	void AsyncWrite(asio::mutable_buffer& buffer);
	// 접속 컨텐츠 코드
	void OnConnect(const boost::system::error_code& err);
	// 버퍼 송신 컨텐츠 코드
	void OnWrite(const boost::system::error_code& err, size_t size);
	// 버퍼 수신 컨텐츠 코드
	void OnRead(const boost::system::error_code& err, size_t size);

	// PacketHeader의 headerCode를 읽고 패킷 클래스 구분
	void HandlePacket(char* ptr, size_t size);

private:
	// UDP
	void AsyncUdpWrite(asio::mutable_buffer& buffer);
	void OnUdpWrite(const boost::system::error_code& err, size_t size);
	void OnUdpRead(const boost::system::error_code& err, size_t size);

private:
	tcp::socket _socket;
	udp::socket _udp_socket;
	udp::endpoint _udp_endpoint;
	static const int RecvBufferSize = 1024;
	char _recvBuffer[RecvBufferSize];
	static const int UdpRecvBufferSize = 1024;
	char _udpRecvBuffer[RecvBufferSize];
	std::string _sendMsg;
	asio::io_context* _io_context;
	UGameInstance* GameInstance;
	TSharedPtr<class NetworkWorker> NetworkThread;
};
