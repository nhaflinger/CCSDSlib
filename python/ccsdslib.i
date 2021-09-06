%module ccsdslib

%include "std_vector.i"
%include "std_string.i"
%include "std_map.i"

%{
#include "CCSDSlib.h"
using namespace CCSDSlib;
%}

namespace std {
%template(map_string_string) map<string, string>;
%template(vector_char) vector<char>;
%template(vector_PacketField) vector<PacketField>;
}

class PacketField {};

struct CCSDSprimaryHeader 
{
    unsigned int packet_version : 3; 
    unsigned int packet_type : 1;
    unsigned int sec_hdr_flag : 1;
    unsigned int apid : 11;
    unsigned int seq_flags : 2;
    unsigned int packet_count_or_name : 14;
    unsigned int packet_length : 16;
};

struct CCSDSsecondaryHeader
{
	unsigned int seconds : 32;
	unsigned int subseconds : 16;
};

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
		
		std::map<std::string, std::string> fieldMap() { return m_field_map; }
		void setFieldMap(std::map<std::string, std::string> map) { m_field_map = map; }

		std::vector<char> encodePacketBytes(CCSDSprimaryHeader& header, const std::vector<PacketField>& packet_fields, const std::map<std::string, std::string>& field_map);
		std::vector<char> encodePacketBytes(CCSDSprimaryHeader& header, const std::vector<PacketField>& packet_fields, const std::map<std::string, double>& field_map);
		std::vector<char> encodePacketBytes(CCSDSprimaryHeader& primary_header, CCSDSsecondaryHeader& secondary_header, const std::vector<PacketField>& packet_fields, const std::map<std::string, std::string>& field_map);
		std::vector<char> encodePacketBytes(CCSDSprimaryHeader& primary_header, CCSDSsecondaryHeader& secondary_header, const std::vector<PacketField>& packet_fields, const std::map<std::string, double>& field_map);
		
		std::vector<char> encodeCommand(CCSDScommandHeader& command_header, CCSDScommandData& command);

	private:
		std::string m_project_name;
		std::vector<PacketField> m_packet_fields;
		PacketFixedLength m_packet_fixed_length;
		CCSDSprimaryHeader m_primary_header;
		CCSDSsecondaryHeader m_secondary_header;
		int m_xtce_apid;
		int m_xtce_sec_hdr_flag;
		int m_xtce_version;
		int m_xtce_type;
	};
}
