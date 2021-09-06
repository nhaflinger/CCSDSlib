#ifndef COMMANDENCODE_H
#define COMMANDENCODE_H

#include <string>
#include <vector>
#include <map>
#include <string.h>
#include "CCSDS.h"
#include "PacketField.h"
#include "CRCchecksum.h"


class CommandEncode
{
public:
	CommandEncode();
	~CommandEncode();

	void setCommandHeader(CCSDScommandHeader &header) { m_command_header = header; }
	void setPacketType(int type) { m_command_header.packet_type = type; }
	void setPacketSeqCount(int seq_cnt) { m_command_header.packet_seq_count = seq_cnt; }
	void setPacketLength(int length) { m_command_header.packet_length = length; }
	void setCommandOpcode(uint32_t opcode) { m_command.command_opcode = opcode; }
	void setDeviceNumber(uint8_t devnum) { m_command.device_number = devnum; }
	void setCommandData(char* data) { memcpy(m_command.command_data, &data[0], COMMAND_DATA_STRING); }
	void setCRC32(uint32_t checksum) { m_command.crc32_checksum = checksum; }

	std::vector<char> encodeCommand(); 
	uint32_t generateCRC32(const char* buf, uint32_t seed, int len);

private:
	void packCommandHeader(); 
	void packOpcode();
	void packDeviceNumber();
	void packCommandData();
	void packCRC32();

	CCSDScommandHeader m_command_header;
	std::vector<char> m_packed_bytes;
	CCSDScommandData m_command;
};

#endif	// COMMANDENCODE_H