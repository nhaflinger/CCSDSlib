#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <map>
#include "PacketField.h"
#include "FrameDecode.h"

class Frame
{
public:
	Frame();
	Frame(const std::vector<PacketField> &frame_fields);
	~Frame();

	void setPacketArray(const std::vector<PacketField> & frame_fields) { m_frame_fields = frame_fields; }
	std::map<std::string, std::string> loadFile(std::string file_path);
	std::map<std::string, std::string> decodeFrame(const std::vector<char> &file_bytes);
	std::vector<char> encodeFrame();

private:
	std::vector<PacketField> m_frame_fields;
	std::vector<char> m_file_bytes;
};

#endif	// FRAME_H