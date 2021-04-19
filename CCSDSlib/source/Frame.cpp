#include "Frame.h"

using namespace std;

Frame::Frame()
{
}

Frame::Frame(const vector<char>& frame_data)
{
	m_frame_data = frame_data;
}

Frame::~Frame()
{
}

map<string, string> Frame::loadFile(string file_path)
{
	map<string, string> field_map;
	ifstream in_file(file_path, ios::binary);
	if (in_file.good())
	{
		in_file.seekg(0, ios::end);
		int num_bytes = (int)in_file.tellg();
		//cout << "Bytes in file: " << " " << num_bytes << " " << "bytes" << endl;

		in_file.seekg(0, ios::beg);
		char c = in_file.get();
		while (in_file.good())
		{
			c = in_file.get();
			m_frame_data.push_back(c);
		}
	}
	else
	{
		cout << "File does not exist!" << endl;
		return field_map;
	}

	TCframeDecode decoder;
	decoder.decodeFrame(m_frame_data);
	field_map = decoder.fieldMap();

	return field_map;
}

map<string, string> Frame::decodeFrame(const vector<char>& file_bytes)
{
	map<string, string> field_map;

	m_frame_data = file_bytes;

	TCframeDecode decoder;
	decoder.decodeFrame(m_frame_data);
	field_map = decoder.fieldMap();

	return field_map;
}

vector<char> Frame::encodeFrame()
{
	vector<char> frame_bytes;

	return frame_bytes;
}