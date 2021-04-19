#ifndef PACKETFIXEDLENGTH_H
#define PACKETFIXEDLENGTH_H

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <map>
#include "PacketField.h"
#include "PacketDecode.h"
#include "PacketEncode.h"

class PacketFixedLength
{
public:
	PacketFixedLength();
	~PacketFixedLength();

	void setPacketArray(const std::vector<PacketField> &packet_fields) { m_packet_fields = packet_fields; }
	std::map<std::string, std::string> loadFile(std::string file_path);
	std::map<std::string, std::string> decodePacket(const std::vector<char> &file_bytes);

	CCSDSprimaryHeader primaryHeader() { return m_primary_header; }
	void setPrimaryHeader(CCSDSprimaryHeader header) { m_primary_header = header; }

	CCSDSsecondaryHeader secondaryHeader() { return m_secondary_header; }
	void setSecondaryHeader(CCSDSsecondaryHeader header) { m_secondary_header = header; }

	std::vector<char> encodePacket(const std::map<std::string, std::string>& field_map, bool secondary_header);

private:
	std::vector<PacketField> m_packet_fields;
	std::vector<char> m_file_bytes;
	CCSDSprimaryHeader m_primary_header;
	CCSDSsecondaryHeader m_secondary_header;
};

#endif	// PACKETFIXEDLENGTH_H