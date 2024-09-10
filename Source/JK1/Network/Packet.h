#include <google/protobuf/message.h>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

using namespace boost;
using namespace std;

enum
{
	TEST_PACKET = 1
};

struct PacketHeader
{
	short Length;
	short Code;
};

class PacketUtil
{
public:
	static size_t RequiredSize(const google::protobuf::Message& msg)
	{
		return sizeof(PacketHeader) + msg.ByteSizeLong();
	}

	static bool Serialize(const asio::mutable_buffer& buffer, const short packetCode, const google::protobuf::Message& msg)
	{
		const size_t requiredSize = RequiredSize(msg);
		if (buffer.size() < requiredSize)
			return false;

		PacketHeader header;
		header.Length = static_cast<short>(msg.ByteSizeLong());
		header.Code = packetCode;

		memcpy(buffer.data(), &header, sizeof(PacketHeader));

		// buffer.data() : ����� ������
		// buffer.data()) + sizeof(PacketHeader) : ����� ���� = payload ������
		char* payloadPtr = static_cast<char*>(buffer.data()) + sizeof(PacketHeader);
		if (!msg.SerializeToArray(payloadPtr, static_cast<int>(buffer.size()) - sizeof(PacketHeader)))
			return false;

		return true;
	}

	static bool ParseHeader(const asio::mutable_buffer& buffer, PacketHeader* header, int& offset)
	{
		// �а� �ִ� �κ��� ���� �ٱ����� ���� ���
		if (buffer.size() <= offset)
			return false;

		// ���� ���� �����Ͱ� ��� ������� ���� ���
		const size_t remainedSize = buffer.size() - offset;
		if (remainedSize < sizeof(PacketHeader))
			return false;

		const char* headerPtr = static_cast<char*>(buffer.data()) + offset;
		memcpy(header, headerPtr, sizeof(PacketHeader));
		offset += sizeof(PacketHeader);

		return true;
	}

	// payloadSize : ����� ������ ������
	// offset : ��� ���ĺ��� ���۵Ǵ� payload ������
	static bool Parse(google::protobuf::Message& msg, const asio::mutable_buffer& buffer, const int payloadSize, int& offset)
	{
		if (buffer.size() < sizeof(PacketHeader))
			return false;

		const char* payloadPtr = static_cast<char*>(buffer.data()) + offset;
		const size_t remainedSize = buffer.size() - offset;
		if (payloadPtr == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Payload Empty!"));
			return false;
		}

		const bool parseResult = msg.ParseFromArray(payloadPtr, payloadSize);
		//const bool parseResult = msg.ParseFromArray(payloadPtr, msg.ByteSizeLong());
		if (parseResult)
		{
			offset += static_cast<int>(msg.ByteSizeLong());
			UE_LOG(LogTemp, Log, TEXT("Parsing Success! offset = %d"), offset);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Parsing Error!"));
			return false;
		}
	}
};

//int main()
//{
//	// ����ȭ
//	Protocol::TEST test;
//	test.set_hp(10);
//	test.set_id(100);
//
//	const size_t requiredSize = PacketUtil::RequiredSize(test);
//	char* rawBuffer = new char[requiredSize];
//	const auto buffer = asio::buffer(rawBuffer, requiredSize);
//	PacketUtil::Serialize(buffer, TEST_PACKET, test);
//
//	// ������ȭ
//	PacketHeader header;
//	char* PacketBuffer = new char[4];
//	int offset = 0;
//	memcpy(PacketBuffer, rawBuffer, 4);
//	auto combinedBuffer = asio::buffer(PacketBuffer, 4);
//	PacketUtil::ParseHeader(combinedBuffer, &header, offset);
//	cout << header.Length << endl;
//	cout << header.Code << endl;
//	delete[] PacketBuffer;
//
//	PacketBuffer = new char[header.Length + sizeof(PacketHeader)];
//	memcpy(PacketBuffer, rawBuffer, offset + header.Length);
//	combinedBuffer = asio::buffer(PacketBuffer, sizeof(PacketHeader));
//
//	Protocol::TEST test2;
//	PacketUtil::Parse(test2, combinedBuffer, header.Length, offset);
//
//	std::cout << test2.hp() << endl;
//
//	return 0;
//}