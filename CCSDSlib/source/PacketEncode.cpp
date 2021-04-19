#ifdef __linux__
//linux code goes here
#elif defined(_WIN32) || defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "PacketEncode.h"
#include "Endian.h"

using namespace std;

PacketEncode::PacketEncode()
{
}

PacketEncode::~PacketEncode()
{
}

vector<char> PacketEncode::encodeFixedLength(const vector<PacketField>& packet_fields, bool secondary_header)
{
	m_packed_bytes.resize(m_primary_header.packet_length);

	packPrimaryHeader();

	if (secondary_header)
	{
		packSecondaryHeader();
	}

	vector<PacketField>::const_iterator it;
	int offset = 0;
	for (it = packet_fields.begin(); it != packet_fields.end(); ++it)
	{
		packBytes((*it).name(), (*it).dataType(), offset + PRIMARY_HEADER_OFFSET, (*it).bitLength() / 8);
		offset += (*it).bitLength() / 8;
	}

	return m_packed_bytes;
}

void PacketEncode::packPrimaryHeader()
{
	//m_packed_bytes.push_back('\0');
	memcpy(&m_packed_bytes[0], (char*)&m_primary_header, PRIMARY_HEADER_OFFSET);
}

void PacketEncode::packSecondaryHeader()
{
	memcpy(&m_packed_bytes[PRIMARY_HEADER_OFFSET], (char*)&m_secondary_header, SECONDARY_HEADER_OFFSET);
}

void PacketEncode::packBytes(string name_val, string data_type, unsigned long offset, unsigned long nbytes)
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
		itmp8 = atoi(m_field_map[name_val].c_str());
		memcpy(&m_packed_bytes[offset], &itmp8, nbytes);
	}
	else if (data_type == "int8_t") {
		itmp8 = atoi(m_field_map[name_val].c_str());
		memcpy(&m_packed_bytes[offset], &itmp8, nbytes);
	}
	else if (data_type == "uint8_t") {
		uitmp8 = atoi(m_field_map[name_val].c_str());
		memcpy(&m_packed_bytes[offset], &uitmp8, nbytes);
	}
	else if (data_type == "bool_t") {
		btmp = atoi(m_field_map[name_val].c_str());
		memcpy(&m_packed_bytes[offset], &btmp, nbytes);
	}
	else if (data_type == "int16_t") {
		itmp16 = _byteswap_16(atoi(m_field_map[name_val].c_str()));
		memcpy(&m_packed_bytes[offset], &itmp16, nbytes);
	}
	else if (data_type == "uint16_t") {
		uitmp16 = _byteswap_16(atoi(m_field_map[name_val].c_str()));
		memcpy(&m_packed_bytes[offset], &uitmp16, nbytes);
	}
	else if (data_type == "int32_t") {
		itmp32 = _byteswap_32(atoi(m_field_map[name_val].c_str()));
		memcpy(&m_packed_bytes[offset], &itmp32, nbytes);
	}
	else if (data_type == "uint32_t") {
		uitmp32 = _byteswap_32(atoi(m_field_map[name_val].c_str()));
		memcpy(&m_packed_bytes[offset], &uitmp32, nbytes);
	}
	else if (data_type == "float_t") {
		ftmp = _byteswap_float((float)atof(m_field_map[name_val].c_str()));
		memcpy(&m_packed_bytes[offset], &ftmp, nbytes);
	}
	else if (data_type == "double_t") {
		dtmp = _byteswap_double(atof(m_field_map[name_val].c_str()));
		memcpy(&m_packed_bytes[offset], &dtmp, nbytes);
	}
	else if (data_type == "vec3_t") {
		string namevalx = name_val + ".x";
		ftmp = _byteswap_float((float)atof(m_field_map[namevalx].c_str()));
		memcpy(&m_packed_bytes[offset], &ftmp, nbytes);

		string namevaly = name_val + ".y";
		ftmp = _byteswap_float((float)atof(m_field_map[namevaly].c_str()));
		memcpy(&m_packed_bytes[offset + 4], &ftmp, nbytes);

		string namevalz = name_val + ".z";
		ftmp = _byteswap_float((float)atof(m_field_map[namevalz].c_str()));
		memcpy(&m_packed_bytes[offset + 8], &ftmp, nbytes);
	}
	else if (data_type == "vec4_t") {
		string namevalx = name_val + ".x";
		ftmp = _byteswap_float((float)atof(m_field_map[namevalx].c_str()));
		memcpy(&m_packed_bytes[offset], &ftmp, nbytes);

		string namevaly = name_val + ".y";
		ftmp = _byteswap_float((float)atof(m_field_map[namevaly].c_str()));
		memcpy(&m_packed_bytes[offset + 4], &ftmp, nbytes);

		string namevalz = name_val + ".z";
		ftmp = _byteswap_float((float)atof(m_field_map[namevalz].c_str()));
		memcpy(&m_packed_bytes[offset + 8], &ftmp, nbytes);

		string namevalw = name_val + ".w";
		ftmp = _byteswap_float((float)atof(m_field_map[namevalw].c_str()));
		memcpy(&m_packed_bytes[offset + 12], &ftmp, nbytes);
	}
}