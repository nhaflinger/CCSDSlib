#ifdef __linux__
//linux code goes here
#elif defined(_WIN32) || defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "FrameDecode.h"
#include "Endian.h"

using namespace std;

TCframeDecode::TCframeDecode()
{
}

TCframeDecode::~TCframeDecode()
{
}

void TCframeDecode::decodeFrame(const vector<char>& file_bytes)
{
	// expect at least the length of the CCSDS primary header
	if (file_bytes.size() < 5)
	{
		cout << "Short frame received: " << file_bytes.size() << " Minimum required is 5 bytes" << endl;
		return;
	}

	auto buffer = &file_bytes[0];

	// read CCSDS frame primary header
	m_primary_header.frame_version = buffer[0] & FRAME_VERSION_MASK;
	m_primary_header.bypass_flag = buffer[0] & BYPASS_FLAG_MASK;
	m_primary_header.ctrl_cmd_flag = buffer[0] & CTRL_CMD_FLAG_MASK;
	m_primary_header.rsvd_spare = buffer[0] & RSVD_SPARE_MASK;
	m_primary_header.spacecraft_id = buffer[0] & SPACECRAFT_ID_MASK;
	m_primary_header.virt_channel_id = buffer[2] & VIRT_CHANNEL_ID_MASK;
	m_primary_header.frame_length = buffer[2] & FRAME_LENGTH_MASK;
	m_primary_header.frame_seq_number = buffer[3] & FRAME_SEQ_NUMBER_MASK;

#ifdef VERBOSE
	cout << "primary header:" << endl;
	cout << "frame_version: " << m_primary_header.frame_version << endl;
	cout << "bypass_flag: " << m_primary_header.bypass_flag << endl;
	cout << "ctrl_cmd_flag: " << m_primary_header.ctrl_cmd_flag << endl;
	cout << "rsvd_spare: " << m_primary_header.rsvd_spare << endl;
	cout << "spacecraft_id: " << m_primary_header.spacecraft_id << endl;
	cout << "virt_channel_id: " << m_primary_header.virt_channel_id << endl;
	cout << "frame_length: " << m_primary_header.frame_length << endl;
	cout << "frame_seq_number: " << m_primary_header.frame_seq_number << endl;
#endif

	unpackBytes();

}

void TCframeDecode::unpackBytes()
{
	// This is all TBD
}


AOSframeDecode::AOSframeDecode()
{
}

AOSframeDecode::~AOSframeDecode()
{
}