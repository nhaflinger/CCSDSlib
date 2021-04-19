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
	Frame(const std::vector<char> & frame_data);
	~Frame();

	void setFrameData(const std::vector<char> & frame_data) { m_frame_data = frame_data; }
	std::map<std::string, std::string> loadFile(std::string file_path);
	std::map<std::string, std::string> decodeFrame(const std::vector<char> &file_bytes);
	std::vector<char> encodeFrame();

private:
	std::vector<char> m_frame_data;
	std::map<std::string, std::string> m_field_map;
};

#endif	// FRAME_H