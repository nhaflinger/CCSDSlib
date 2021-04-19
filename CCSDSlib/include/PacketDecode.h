#ifndef PACKETDECODE_H
#define PACKETDECODE_H

#include <string>
#include <vector>
#include <map>
#include "CCSDS.h"
#include "PacketField.h"

class PacketDecode
{
public:
	PacketDecode();
	~PacketDecode();

	std::map<std::string, std::string> fieldMap() { return m_field_map; }
	int decodePrimaryHeader(const std::vector<char>& file_bytes);
	int decodeSecondaryHeader(const std::vector<char>& file_bytes);
	void decodeFixedLength(const std::vector<char> &file_bytes, const std::vector<PacketField> &packet_fields);
	CCSDSprimaryHeader primaryHeader() { return m_primary_header; }
	CCSDSsecondaryHeader secondaryHeader() { return m_secondary_header; }

private:
	void unpackBytes(const char* buffer, std::map<std::string, std::string>::iterator ik, std::string name_val, std::string data_type, int offset, int nbytes);

	CCSDSprimaryHeader m_primary_header;
	CCSDSsecondaryHeader m_secondary_header;
	std::map<std::string, std::string> m_field_map;
};

#endif// PACKETDECODE_H