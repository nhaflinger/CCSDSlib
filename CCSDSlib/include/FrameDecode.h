#ifndef FRAMEDECODE_H
#define FRAMEDECODE_H

#include <string>
#include <vector>
#include <map>
#include "CCSDS.h"
#include "PacketField.h"

class TCframeDecode
{
public:
	TCframeDecode();
	~TCframeDecode();

	void decodeFrame(const std::vector<char>& file_bytes);
	TCtransferFramePrimaryHeader primaryHeader() { return m_primary_header; }
	std::map<std::string, std::string> fieldMap() { return m_field_map; };

private:
	void unpackBytes();

	TCtransferFramePrimaryHeader m_primary_header;
	std::map<std::string, std::string> m_field_map;
};

class AOSframeDecode
{
public:
	AOSframeDecode();
	~AOSframeDecode();

	//void decodeFrame(const std::vector<char>& file_bytes, const std::vector<PacketField>& frame_fields);
	//AOStransferFramePrimaryHeader primaryHeader() { return m_primary_header; }

private:
	//void unpackBytes();

	//AOStransferFramePrimaryHeader m_primary_header;
};

#endif	// FRAMEDECODE_H