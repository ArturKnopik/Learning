#pragma once

#include <array>
#include <cstring>
#include <string_view>

using DataSize_t = uint32_t;
constexpr DataSize_t NET_MESSAGE_BUFFER_SIZE = 1024 * 20; //20 Kib

struct MessageContent {
	uint8_t* m_begin = nullptr;
	DataSize_t m_size = 0;
	MessageContent(uint8_t* begin, DataSize_t size);
};

class Message {
public:
	Message() = default;

	~Message() = default;

	void skipBytes(DataSize_t count);

	void addByte(uint8_t value);

	uint8_t getByte();

	/*

	SETTERS
		void Message::addUint16(uint8_t value);
		void Message::addUint32(uint8_t value);
		void Message::addUint64(uint8_t value);
		void Message::addInt16(uint8_t value);
		void Message::addInt32(uint8_t value);
		void Message::addInt64(uint8_t value);

	GETTERS
		uint16_t Message::getUint16();
		uint32_t Message::addUint32();
		uint64_t Message::addUint64();
		int16_t Message::addInt16();
		int32_t Message::addInt32();
		int64_t Message::addInt64();
	*/

	void addString(std::string_view value);

	std::string getString();

	bool addBytes(const uint8_t* bytes, DataSize_t size);

	void reset();

	bool setBufferPosition(DataSize_t pos);

	MessageContent getMessageInfo();

	std::array<uint8_t, NET_MESSAGE_BUFFER_SIZE> m_data = { 0 };

	void setLenght(DataSize_t lenght);
private:
	bool canRead(DataSize_t size);

	bool canAdd(DataSize_t size);

	struct NetworkMessageInfo
	{
		DataSize_t length = 0;
		DataSize_t position = 0;
	};

	NetworkMessageInfo m_info;

};