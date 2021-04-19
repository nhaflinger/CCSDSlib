#ifdef __linux__
//linux code goes here
#elif defined(_WIN32) || defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "CommandEncode.h"
#include "Endian.h"

using namespace std;

CommandEncode::CommandEncode()
{
	m_command_header.packet_type = 0;
	m_command_header.packet_seq_count = 0;
	m_command_header.packet_length = 44;
}

CommandEncode::~CommandEncode()
{
}

void CommandEncode::packCommandHeader()
{
	memcpy(&m_packed_bytes[0], (char*)&m_command_header, COMMAND_HEADER_OFFSET);
}

void CommandEncode::packOpcode()
{
	//uint32_t opcode = _byteswap_32(m_command_data.command_opcode);
	uint32_t opcode = m_command.command_opcode;
	memcpy(&m_packed_bytes[COMMAND_HEADER_OFFSET], &opcode, COMMAND_OPCODE);
}

void CommandEncode::packDeviceNumber()
{
	uint8_t devnum = m_command.device_number;
	memcpy(&m_packed_bytes[COMMAND_HEADER_OFFSET + COMMAND_OPCODE], &devnum, COMMAND_DEVICE_NUMBER);
}

void CommandEncode::packCRC32()
{
	//uint32_t crc32 = _byteswap_32(m_command_data.crc32_checksum);
	uint32_t crc32 = m_command.crc32_checksum;
	memcpy(&m_packed_bytes[COMMAND_HEADER_OFFSET + COMMAND_OPCODE + COMMAND_DEVICE_NUMBER + COMMAND_DATA_STRING], &crc32, COMMAND_CRC32);
}

void CommandEncode::packCommandData()
{
	memcpy(&m_packed_bytes[COMMAND_HEADER_OFFSET + COMMAND_OPCODE + COMMAND_DEVICE_NUMBER], m_command.command_data, COMMAND_DATA_STRING);
}

vector<char> CommandEncode::encodeCommand()
{
	m_packed_bytes.resize(m_command_header.packet_length);

	packCommandHeader();
	packOpcode();
	packDeviceNumber();
	packCommandData();
	packCRC32();

	return m_packed_bytes;
}

uint32_t CommandEncode::generateCRC32(const char* buf, uint32_t seed, int len)
{
	CRCchecksum cksumgen;
	return cksumgen.crc32_checksum(seed, buf, len);
}