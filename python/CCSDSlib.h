#ifndef CCSDSLIB_H
#define CCSDSLIB_H

#include "rapidxml.hpp"
#include "PacketField.h"
#include "PacketFixedLength.h"
#include "PacketDecode.h"
#include "PacketEncode.h"
#include "Frame.h"
#include "FrameDecode.h"
#include "CommandEncode.h"

struct ParamNameType {
	std::string name;
	std::string type;
}; 

namespace CCSDSlib
{
	class CCSDS
	{
	public:
		CCSDS();
		~CCSDS();

		void newPacketField(std::string name, std::string data_type, int bit_length, int bit_offset, int byte_order);
		void xmlPacketDesc(std::string file_path, std::string root_node, int byte_order);

		int xtceAPID() { return m_xtce_apid; }
		int xtceSecHdrFlag() { return m_xtce_sec_hdr_flag; }
		int xtceVersion() { return m_xtce_version; }
		int xtceType() { return m_xtce_type; }

		std::map<std::string, std::string> loadPacketFile(std::string file_path);
		std::map<std::string, std::string> decodePacketBytes(const std::vector<char> &file_bytes);

		CCSDSprimaryHeader primaryHeader() { return m_primary_header; }
		CCSDSsecondaryHeader secondaryHeader() { return m_secondary_header; }

		std::map<std::string, std::string> loadFrameFile(std::string file_path);
		std::map<std::string, std::string> decodeFrameBytes(const std::vector<char> &file_bytes);

		std::vector<PacketField> packetFields() { return m_packet_fields; }

		// need a method to set byte_order on PacketField 

		std::map<std::string, std::string> fieldMap() { return m_field_map; }
		void setFieldMap(std::map<std::string, std::string> map) { m_field_map = map; }

		std::vector<char> encodePacketBytes(CCSDSprimaryHeader& header, const std::vector<PacketField>& packet_fields, const std::map<std::string, std::string>& field_map);
		std::vector<char> encodePacketBytes(CCSDSprimaryHeader& header, const std::vector<PacketField>& packet_fields, const std::map<std::string, double>& field_map);
		std::vector<char> encodePacketBytes(CCSDSprimaryHeader& primary_header, CCSDSsecondaryHeader& secondary_header, const std::vector<PacketField>& packet_fields, const std::map<std::string, std::string>& field_map);
		std::vector<char> encodePacketBytes(CCSDSprimaryHeader& primary_header, CCSDSsecondaryHeader& secondary_header, const std::vector<PacketField>& packet_fields, const std::map<std::string, double>& field_map);

		std::vector<char> encodeCommand(CCSDScommandHeader& command_header, CCSDScommandData& command);

	private:
		std::string m_project_name;
		std::map<std::string, std::string> m_field_map;
		std::vector<PacketField> m_packet_fields;
		PacketFixedLength m_packet_fixed_length;
		CCSDSprimaryHeader m_primary_header;
		CCSDSsecondaryHeader m_secondary_header;
		int m_xtce_apid;
		int m_xtce_sec_hdr_flag;
		int m_xtce_version;
		int m_xtce_type;
		CCSDScommandHeader m_command_header;
	};
}

#endif	// CCSDSLIB_H