#pragma once

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <string_view>

static constexpr std::size_t HEADER_LENGTH = 4;
static constexpr std::size_t MAX_BODY_LENGTH = 1024 * 10;
static constexpr std::size_t NETWORKMESSAGE_MAXSIZE = HEADER_LENGTH + MAX_BODY_LENGTH;
static constexpr uint16_t INITIAL_BUFFER_POSITION = HEADER_LENGTH;

class Message
{
public:
	Message();

	uint8_t getByte();

	uint8_t getPreviousByte();

	std::string_view getString(uint16_t stringLen = 0);
	// skips count unknown/unused bytes in an incoming message
	void skipBytes(int16_t count) { info.position += count; }

	// simply write functions for outgoing message
	void addByte(uint8_t value);

	void addString(std::string_view value);

	uint16_t getLength() const;

	void setLength(uint16_t newLength);

	uint16_t getBufferPosition() const;

	bool setBufferPosition(uint16_t pos);

	uint8_t* getBuffer();

	const uint8_t* getBuffer() const;

	uint8_t* getBodyBuffer();

	void writeMessageLength() { add_header(info.length); }

	uint16_t getLengthFromHeader() const { return static_cast<uint16_t>(m_buffer[0] | m_buffer[1] << 8); }

	template <typename T>
	void add(T value)
	{
		if (!canAdd(sizeof(T))) {
			return;
		}

		std::memcpy(m_buffer.data() + info.position, &value, sizeof(T));
		info.position += sizeof(T);
		info.length += sizeof(T);
	}

	template <typename T>
	std::enable_if_t<std::is_trivially_copyable_v<T>, T> get() noexcept
	{
		static_assert(std::is_trivially_constructible_v<T>, "Destination type must be trivially constructible");

		if (!canRead(sizeof(T))) {
			return 0;
		}

		T value;
		std::memcpy(&value, m_buffer.data() + info.position, sizeof(T));
		info.position += sizeof(T);
		return value;
	}

	void add_header(uint16_t value) { std::memcpy(m_buffer.data(), &value, sizeof(uint16_t)); }

	void reset() { info = {}; }

protected:
	struct NetworkMessageInfo
	{
		uint16_t length = 0;
		uint16_t position = HEADER_LENGTH;
	};

	NetworkMessageInfo info;

private:
	bool canAdd(size_t size) const { return (size + info.position) < MAX_BODY_LENGTH; }

	bool canRead(int32_t size)
	{
		if ((info.position + size) > (info.length + 8) || size >= (MAX_BODY_LENGTH - info.position)) {
			return false;
		}
		return true;
	}

	std::array<uint8_t, HEADER_LENGTH + MAX_BODY_LENGTH> m_buffer{0};
};