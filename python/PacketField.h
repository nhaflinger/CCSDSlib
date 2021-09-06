#ifndef PACKETFIELD_H
#define PACKETFIELD_H

#include <iostream>
#include <string>
#include <map>


class PacketField
{
public:
	PacketField();
	PacketField(std::string name, std::string data_type, int bit_length, int byte_order);
	PacketField(std::string name, std::string data_type, int bit_length, int bit_offset, int byte_order);
	~PacketField() {};
	
	void populate();
	std::map<std::string, std::string> packetFields() const { return m_packet_fields; }
	std::string name() const { return m_name; }
	std::string dataType() const { return m_data_type; }
	int bitLength() const { return m_bit_length; }
	int bitOffset() const { return m_bit_offset; }
	int byteOrder() const { return m_byte_order; }
	void setName(std::string name) { m_name = name; }
	void setDataType(std::string type) { m_data_type = type; }
	void setBitLength(int length) { m_bit_length = length; }
	void setBitOffset(int offset) { m_bit_offset = offset; }
	void setByteOrder(int order) { m_byte_order = order; }

private:
	std::string m_name;
	std::string m_data_type;
	int m_bit_length;
	int m_bit_offset;
	int m_byte_order;
	std::map<std::string, std::string> m_packet_fields;
};

#endif	// PACKETFIELD_H
