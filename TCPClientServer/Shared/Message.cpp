#include "Message.h"

#include <math.h>
#include <iostream>

void Message::skipBytes(DataSize_t count)
{
	m_info.position += count;
}

void Message::addByte(uint8_t value)
{
	if (!canAdd(1)) {
		return;
	}

	m_data[m_info.position++] = value;
	m_info.length++;
}

uint8_t Message::getByte()
{
	if (!canRead(1)) {
		return 0;
	}

	return m_data[m_info.position++];
}

void Message::reset()
{
	m_info = {};
}

bool Message::setBufferPosition(DataSize_t pos)
{
	if (pos < NET_MESSAGE_BUFFER_SIZE)
	{
		m_info.position = pos;
		return true;
	}
	return false;
}

void Message::addString(std::string_view value)
{
	DataSize_t stringLen = static_cast<DataSize_t>(value.size());
	if (!canAdd(stringLen + sizeof(DataSize_t)))
	{
		return;
	}
	// adding string size
	std::memcpy(m_data.data() + m_info.position, &stringLen, stringLen);
	m_info.position += stringLen;
	m_info.length += stringLen;

	// adding string content
	std::memcpy(m_data.data() + m_info.position, value.data(), stringLen);
	m_info.position += stringLen;
	m_info.length += stringLen;
}

std::string Message::getString()
{
	// reading string size
	DataSize_t stringLen = 0;
	std::memcpy(&stringLen, m_data.data() + m_info.position, sizeof(DataSize_t));

	m_info.position += (sizeof(DataSize_t));

	// reading string content
	if (!canRead(stringLen)) {
		return {};
	}

	uint8_t* data = m_data.data() + m_info.position;
	m_info.position += stringLen;
	return std::string(reinterpret_cast<char*>(data), stringLen);
}

bool Message::addBytes(const uint8_t* bytes, DataSize_t size)
{
	if (!canAdd(size)) {
		return false;
	}

	std::memcpy(m_data.data() + m_info.position, bytes, size);
	m_info.position += size;
	m_info.length += size;
	return true;
}

bool Message::canAdd(DataSize_t size) {
	return (size + m_info.position) < NET_MESSAGE_BUFFER_SIZE;
}

void Message::setLenght(DataSize_t lenght)
{
	m_info.length = lenght;
}

bool Message::canRead(DataSize_t size)
{
	if ((m_info.position + size) > (m_info.length) || size >= (NET_MESSAGE_BUFFER_SIZE - m_info.position)) {
		return false;
	}
	return true;
}


MessageContent Message::getMessageInfo()
{
	return  MessageContent(m_data.data(), m_info.length);
}

MessageContent::MessageContent(uint8_t* begin, DataSize_t size)
	: m_begin(begin), m_size(size)
{
}
