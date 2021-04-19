#ifdef __linux__
//linux code goes here
#elif defined(_WIN32) || defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "PacketDecode.h"
#include "Endian.h"

using namespace std;

PacketDecode::PacketDecode()
{
}

PacketDecode::~PacketDecode()
{
}

int PacketDecode::decodePrimaryHeader(const vector<char>& file_bytes)
{
	// expect at least the length of the CCSDS primary header
	if (file_bytes.size() < 6)
	{
		cout << "Short packet received: " << file_bytes.size() << " Minimum required is 6 bytes" << endl;
		return 0;
	}

	auto buffer = &file_bytes[0];

	// read CCSDS packet primary header
	m_primary_header.packet_version = buffer[1] & PACKET_VERSION_MASK;
	m_primary_header.packet_type = buffer[1] & PACKET_TYPE_MASK;
	m_primary_header.sec_hdr_flag = buffer[1] & SEQ_HDR_FLAG_MASK;
	m_primary_header.apid = buffer[1] & APID_MASK;
	m_primary_header.seq_flags = buffer[3] & SEQ_FLAGS_MASK;
	m_primary_header.packet_count_or_name = buffer[3] & PACKET_COUNT_MASK;
	m_primary_header.packet_length = buffer[5] & PACKET_LENGTH_MASK;

	return 1;
}

int PacketDecode::decodeSecondaryHeader(const vector<char>& file_bytes)
{
	auto buffer = &file_bytes[0];

	// read CCSDS packet secondary header
	m_secondary_header.seconds = buffer[0] & SECONDS_MASK;
	m_secondary_header.subseconds = buffer[4] & SUBSECONDS_MASK;

	return 1;
}

void PacketDecode::decodeFixedLength(const vector<char>& file_bytes, const vector<PacketField>& packet_fields)
{
	int status;
	status = decodePrimaryHeader(file_bytes);

	// do something if there is a secondary header
	int secondary_header_offset = 0;
	if (m_primary_header.sec_hdr_flag)
	{
		status = decodeSecondaryHeader(file_bytes);
		secondary_header_offset = SECONDARY_HEADER_OFFSET;
	}

	auto buffer = &file_bytes[0];

	vector<PacketField>::const_iterator it;
	int offset = 0;
	for (it = packet_fields.begin(); it != packet_fields.end(); ++it)
	{
		map<string, string>::iterator ik = m_field_map.begin();
		unpackBytes(buffer, ik, (*it).name(), (*it).dataType(), offset + PRIMARY_HEADER_OFFSET + secondary_header_offset, (*it).bitLength() / 8);
		offset += (*it).bitLength() / 8;
	}
}

void PacketDecode::unpackBytes(const char* buffer, map<string, string>::iterator ik, string name_val, string data_type, int offset, int nbytes)
{
	float ftmp;
	double dtmp;
	int8_t itmp8;
	uint8_t uitmp8;
	int16_t itmp16;
	uint16_t uitmp16;
	int32_t itmp32;
	uint32_t uitmp32;
	bool btmp;

	if (data_type == "char_t") {
		memcpy(&itmp8, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(itmp8) });
	}
	else if (data_type == "int8_t") {
		memcpy(&itmp8, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(itmp8) });
	}
	else if (data_type == "uint8_t") {
		memcpy(&uitmp8, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(uitmp8) });
	}
	else if (data_type == "bool_t") {
		memcpy(&btmp, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(btmp) });
	}
	else if (data_type == "int16_t") {
		memcpy(&itmp16, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(_byteswap_16(itmp16)) });
	}
	else if (data_type == "uint16_t") {
		memcpy(&uitmp16, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(_byteswap_16(uitmp16)) });
	}
	else if (data_type == "int32_t") {
		memcpy(&itmp32, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(_byteswap_32(itmp32)) });
	}
	else if (data_type == "uint32_t") {
		memcpy(&uitmp32, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(_byteswap_32(uitmp32)) });
	}
	else if (data_type == "float_t") {
		memcpy(&ftmp, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(_byteswap_float(ftmp)) });
	}
	else if (data_type == "double_t") {
		memcpy(&dtmp, &buffer[offset], nbytes);
		m_field_map.insert(ik, { name_val, to_string(_byteswap_double(dtmp)) });
	}
	else if (data_type == "vec3_t") {
		memcpy(&ftmp, &buffer[offset], 4);
		string namevalx = name_val + ".x";
		m_field_map.insert(ik, { namevalx, to_string(_byteswap_float(ftmp)) });
		memcpy(&ftmp, &buffer[offset + 4], 4);
		string namevaly = name_val + ".y";
		m_field_map.insert(ik, { namevaly, to_string(_byteswap_float(ftmp)) });
		memcpy(&ftmp, &buffer[offset + 8], 4);
		string namevalz = name_val + ".z";
		m_field_map.insert(ik, { namevalz, to_string(_byteswap_float(ftmp)) });
	}
	else if (data_type == "vec4_t") {
		memcpy(&ftmp, &buffer[offset], 4);
		string namevalx = name_val + ".x";
		m_field_map.insert(ik, { namevalx, to_string(_byteswap_float(ftmp)) });
		memcpy(&ftmp, &buffer[offset + 4], 4);
		string namevaly = name_val + ".y";
		m_field_map.insert(ik, { namevaly, to_string(_byteswap_float(ftmp)) });
		memcpy(&ftmp, &buffer[offset + 8], 4);
		string namevalz = name_val + ".z";
		m_field_map.insert(ik, { namevalz, to_string(_byteswap_float(ftmp)) });
		memcpy(&ftmp, &buffer[offset + 12], 4);
		string namevalw = name_val + ".w";
		m_field_map.insert(ik, { namevalw, to_string(_byteswap_float(ftmp)) });
	}
}