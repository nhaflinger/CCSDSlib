#ifndef PACKETENCODE_H
#define PACKETENCODE_H

#include <string>
#include <vector>
#include <map>
#include "CCSDS.h"
#include "PacketField.h"


class PacketEncode
{
public:
	PacketEncode();
	~PacketEncode();

	void setPrimaryHeader(CCSDSprimaryHeader &header) { m_primary_header = header; }
	void setPacketAPID(int apid) { m_primary_header.apid = apid; }
	void setPacketVersion(int version) { m_primary_header.packet_version = version; }
	void setPacketType(int type) { m_primary_header.packet_type = type; }
	void setPacketSecHdrFlag(int sechdrflg) { m_primary_header.sec_hdr_flag = sechdrflg; }
	void setPacketSeqFlags(int seqflgs) { m_primary_header.seq_flags = seqflgs; }
	void setPacketCountOrName(int count) { m_primary_header.packet_count_or_name = count; }
	void setPacketLength(int length) { m_primary_header.packet_length = length; }
	void setSecondaryHeader(CCSDSsecondaryHeader& header) { m_secondary_header = header; }

	void setFieldMap(std::map<std::string, std::string> field_map) { m_field_map = field_map; }
	void setFieldMapValue(std::string name, std::string val) { m_field_map.insert(std::pair<std::string, std::string>(name, val)); };

	std::vector<char> encodeFixedLength(const std::vector<PacketField>& packet_fields, bool secondary_header);

private:
	void packPrimaryHeader();
	void packSecondaryHeader();
	void packBytes(std::string name_val, std::string data_type, unsigned long offset, unsigned long nbytes);

	CCSDSprimaryHeader m_primary_header;
	CCSDSsecondaryHeader m_secondary_header;
	std::map<std::string, std::string> m_field_map;
	std::vector<char> m_packed_bytes;
};

#endif	// PACKETENCODE_H
