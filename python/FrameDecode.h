#ifndef FRAMEDECODE_H
#define FRAMEDECODE_H

#include <string>
#include <vector>
#include <map>
#include "CCSDS.h"
#include "PacketField.h"

class FrameDecode
{
public:
	FrameDecode();
	~FrameDecode();

	void decodeFrame(const std::vector<char>& file_bytes, const std::vector<PacketField>& frame_fields);
	std::map<std::string, std::string> fieldMap() { return m_field_map; }
	CCSDSframePrimaryHeader primaryHeader() { return m_primary_header; }

private:
	void unpackBytes(const char* buffer, std::map<std::string, std::string>::iterator ik, std::string name_val, std::string data_type, int offset, int nbytes);

	CCSDSframePrimaryHeader m_primary_header;
	std::map<std::string, std::string> m_field_map;
};

#endif	// FRAMEDECODE_H