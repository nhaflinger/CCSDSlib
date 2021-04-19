#ifdef __linux__
//linux code goes here
#elif defined(_WIN32) || defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "PacketFixedLength.h"

using namespace std;

PacketFixedLength::PacketFixedLength()
{
}

PacketFixedLength::~PacketFixedLength()
{
}

map<string, string> PacketFixedLength::loadFile(string file_path)
{
	map<string, string> field_map;

	ifstream in_file(file_path, ios::binary);
	if (in_file.good())
	{
		in_file.seekg(0, ios::end);
		int num_bytes = (int)in_file.tellg();

		in_file.seekg(0, ios::beg);
		char c = in_file.get();
		m_file_bytes.push_back('\0');
		while (in_file.good())
		{
			c = in_file.get();
			m_file_bytes.push_back(c);
		}
	}
	else
	{
		cout << "File does not exist!" << endl;
	}

	PacketDecode decoder;
	decoder.decodeFixedLength(m_file_bytes, m_packet_fields);
	field_map = decoder.fieldMap();
	m_primary_header = decoder.primaryHeader();

	return field_map;
}

map<string, string> PacketFixedLength::decodePacket(const vector<char>& file_bytes)
{
	map<string, string> field_map;

	m_file_bytes = file_bytes;

	PacketDecode decoder;
	decoder.decodeFixedLength(m_file_bytes, m_packet_fields);
	field_map = decoder.fieldMap();
	m_primary_header = decoder.primaryHeader();

	return field_map;
}

vector<char> PacketFixedLength::encodePacket(const map<string, string>& field_map, bool secondary_header)
{
	PacketEncode encoder;
	encoder.setPrimaryHeader(m_primary_header);
	if (secondary_header)
	{
		encoder.setSecondaryHeader(m_secondary_header);
	}
	encoder.setFieldMap(field_map);

	vector<char> packed_bytes = encoder.encodeFixedLength(m_packet_fields, secondary_header);

	return packed_bytes;
}