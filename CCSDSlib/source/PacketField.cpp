#ifdef __linux__
//linux code goes here
#elif defined(_WIN32) || defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "PacketField.h"

using namespace std;

PacketField::PacketField()
{
}

PacketField::PacketField(string name, string data_type, int bit_length, int byte_order)
{
	m_name = name;
	m_data_type = data_type;
	m_bit_length = bit_length;
	m_bit_offset = -1;
	m_byte_order = byte_order;

	populate();
}

PacketField::PacketField(string name, string data_type, int bit_length, int bit_offset, int byte_order)
{
	m_name = name;
	m_data_type = data_type;
	m_bit_length = bit_length;
	m_bit_offset = bit_offset;
	m_byte_order = byte_order;

	populate();
}

void PacketField::populate()
{
	map<string, string>::iterator it = m_packet_fields.begin();
	m_packet_fields.insert(it, { string("name"), m_name });
	m_packet_fields.insert(it, { string("data_type"), m_data_type });
	m_packet_fields.insert(it, { string("bit_length"), to_string(m_bit_length) });
	m_packet_fields.insert(it, { string("bit_offset"), to_string(m_bit_offset) });
	m_packet_fields.insert(it, { string("byte_order"), to_string((int)m_byte_order) });
}