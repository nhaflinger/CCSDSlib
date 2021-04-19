#ifdef __linux__
//linux code goes here
#elif defined(_WIN32) || defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "FrameEncode.h"
#include "Endian.h"

using namespace std;

TCframeEncode::TCframeEncode()
{
}

TCframeEncode::~TCframeEncode()
{
}

vector<char> TCframeEncode::encodeFrameData()
{
	m_packed_bytes.resize(m_primary_header.frame_length);

	packPrimaryHeader();

	packBytes();

	return m_packed_bytes;
}

void TCframeEncode::packPrimaryHeader()
{
	//m_packed_bytes.push_back('\0');
	memcpy(&m_packed_bytes[0], (char*)&m_primary_header, TC_TRANSFER_FRAME_PRIMARY_HEADER_OFFSET);
}

void TCframeEncode::packBytes()
{
	// this is all TBD
}

AOSframeEncode::AOSframeEncode()
{
}

AOSframeEncode::~AOSframeEncode()
{
}