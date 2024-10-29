#include "PacketSession.h"
#include "NetworkWorker.h"
#include "ClientPacketHandler.h"

PacketSession::PacketSession(asio::io_context* io_context)
	: _socket(*io_context)
	, _io_context(io_context)
	, _udp_socket(*io_context)
{
	ClientPacketHandler::Init();
	memset(_recvBuffer, 0, RecvBufferSize);
	memset(_udpRecvBuffer, 0, UdpRecvBufferSize);
	GameInstance = GWorld->GetGameInstance();

}

//PacketSession::PacketSession(TWeakPtr<asio::io_context> io_context)
//	: _socket(*io_context.Pin().Get()), _ioContextRef(io_context)
//{
//	ClientPacketHandler::Init();
//	
//	memset(_recvBuffer, 0, RecvBufferSize);
//}

PacketSession::~PacketSession()
{
	if (NetworkThread != nullptr)
	{
		_io_context->stop();
		delete _io_context;
		//_io_context = nullptr;
		NetworkThread->Destroy();
		NetworkThread = nullptr;
	}
}

void PacketSession::Run()
{
	NetworkThread = MakeShared<NetworkWorker>(AsShared());
}

void PacketSession::Run(TSharedPtr<asio::io_context> io_context)
{
	NetworkThread = MakeShared<NetworkWorker>(io_context, AsShared());
}

void PacketSession::Connect(std::string host, int port)
{
	tcp::endpoint endpoint(asio::ip::make_address(host), port);

	_udp_endpoint = udp::endpoint(asio::ip::make_address(host), port);
	_udp_socket.open(udp::v4());
	_udp_socket.bind(udp::endpoint(udp::v4(), 0));
	_socket.async_connect(
		endpoint,
		boost::bind(
			&PacketSession::OnConnect,
			this,
			asio::placeholders::error
		)
	);
}

void PacketSession::AsyncWrite(asio::mutable_buffer& buffer)
{
	asio::async_write(
		_socket,
		buffer,
		boost::bind(
			&PacketSession::OnWrite,
			this,
			asio::placeholders::error,
			asio::placeholders::bytes_transferred
		)
	);
}

void PacketSession::OnConnect(const boost::system::error_code& err)
{
	if (!err)
	{
		UE_LOG(LogTemp, Log, TEXT("Connect Success"));
		//MakeLoginReq(1000);
		AsyncRead();
		AsyncUdpRead();

	}
	else
	{
		// TODO : Error Code
		// Use FString::Printf with converted string
		UE_LOG(LogTemp, Error, TEXT("%s"), err.message().c_str());
	}
}

void PacketSession::OnWrite(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{
		UE_LOG(LogTemp, Error, TEXT("OnWrite : %d"), size);
	}
	else
	{
		// TODO : Error Code
	}
}

void PacketSession::AsyncRead()
{
	memset(_recvBuffer, 0, RecvBufferSize);
	_socket.async_read_some(
		asio::buffer(
			_recvBuffer,
			RecvBufferSize
		),
		boost::bind(
			&PacketSession::OnRead,
			this,
			asio::placeholders::error,
			asio::placeholders::bytes_transferred
		)
	);
}

void PacketSession::AsyncUdpRead()
{
	memset(_udpRecvBuffer, 0, UdpRecvBufferSize);
	udp::endpoint sender_endpoint;
	_udp_socket.async_receive(
		asio::buffer(
			_udpRecvBuffer,
			UdpRecvBufferSize
		),
		boost::bind(
			&PacketSession::OnUdpRead,
			this,
			asio::placeholders::error,
			asio::placeholders::bytes_transferred
		)
	);
}

void PacketSession::OnRead(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{
		HandlePacket(_recvBuffer, size);
		AsyncRead();
	}
	else
	{
		// TODO : Error
	}
}

void PacketSession::HandlePacket(char* ptr, size_t size)
{
	PacketSessionRef session = this->AsShared();
	ClientPacketHandler::HandlePacket(session, ptr, size);
}

void PacketSession::AsyncUdpWrite(asio::mutable_buffer& buffer)
{
	//udp::endpoint remote_edpoint;
	_udp_socket.async_send_to (
		buffer,
		_udp_endpoint,
		boost::bind(
			&PacketSession::OnUdpWrite,
			this,
			asio::placeholders::error,
			asio::placeholders::bytes_transferred
		)
	);
}

void PacketSession::OnUdpWrite(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{
		UE_LOG(LogTemp, Log, TEXT("OnWrite : %d"), size);
	}
	else
	{
		// TODO : Error Code
		string line = err.message();
		line.append("");
	}
}

void PacketSession::OnUdpRead(const boost::system::error_code& err, size_t size)
{
	if (!err)
	{
		HandlePacket(_udpRecvBuffer, size);
		AsyncUdpRead();
	}
	else
	{
		// TODO : Error
		string line = err.message();
		line.append("");
	}
}
