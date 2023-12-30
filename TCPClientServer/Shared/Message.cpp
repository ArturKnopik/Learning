#include "Message.h"

Message::Message() {}

uint8_t Message::getByte()
{
	if (!canRead(1)) {
		return 0;
	}

	return m_buffer[info.position++];
}

uint8_t Message::getPreviousByte() { return m_buffer[--info.position]; }

std::string_view Message::getString(uint16_t stringLen)
{
	if (stringLen == 0) {
		stringLen = get<uint16_t>();
	}

	if (!canRead(stringLen)) {
		return {};
	}

	uint8_t* it = m_buffer.data() + info.position;
	info.position += stringLen;
	return {reinterpret_cast<char*>(it), stringLen};
}

void Message::addByte(uint8_t value)
{
	if (!canAdd(1)) {
		return;
	}

	m_buffer[info.position++] = value;
	info.length++;
}

void Message::addString(std::string_view value)
{
	uint16_t stringLen = static_cast<uint16_t>(value.size());
	if (!canAdd(stringLen + 1) || stringLen > MAX_BODY_LENGTH / 8 - 4) {
		return;
	}

	add<uint16_t>(stringLen);
	std::memcpy(m_buffer.data() + info.position, value.data(), stringLen);
	info.position += stringLen;
	info.length += stringLen;
}

uint16_t Message::getLength() const { return info.length; }

void Message::setLength(uint16_t newLength) { info.length = newLength; }

uint16_t Message::getBufferPosition() const { return info.position; }

bool Message::setBufferPosition(uint16_t pos)
{
	if (pos < NETWORKMESSAGE_MAXSIZE - INITIAL_BUFFER_POSITION) {
		info.position = pos + INITIAL_BUFFER_POSITION;
		return true;
	}
	return false;
}

uint8_t* Message::getBuffer() { return &m_buffer[0]; }

const uint8_t* Message::getBuffer() const { return &m_buffer[0]; }

uint8_t* Message::getBodyBuffer()
{
	info.position = sizeof(uint16_t);
	return &m_buffer[HEADER_LENGTH];
}
