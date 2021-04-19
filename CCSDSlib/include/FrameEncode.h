#ifndef FRAMEENCODE_H
#define FRAMEENCODE_H

#include <string>
#include <vector>
#include <map>
#include "CCSDS.h"
#include "PacketField.h"


class TCframeEncode
{
public:
	TCframeEncode();
	~TCframeEncode();

	void setPrimaryHeader(TCtransferFramePrimaryHeader& header) { m_primary_header = header; }
	void setFrameVersion(int frame_version) { m_primary_header.frame_version = frame_version; }
	void setBypassFlag(int bypass_flag) { m_primary_header.bypass_flag = bypass_flag; }
	void setCtrlCmdFlag(int ctrl_cmd_flag) { m_primary_header.ctrl_cmd_flag = ctrl_cmd_flag; }
	void setRsvdSpare(int rsvd_spare) { m_primary_header.rsvd_spare = rsvd_spare; }
	void setSpacecraftID(int spacecraft_id) { m_primary_header.spacecraft_id = spacecraft_id; }
	void setVirtChannelID(int virt_channel_id) { m_primary_header.virt_channel_id = virt_channel_id; }
	void setFrameLength(int frame_length) { m_primary_header.frame_length = frame_length; }
	void setFrameSeqNumber(int frame_seq_number) { m_primary_header.frame_seq_number = frame_seq_number; }

	std::vector<char> encodeFrameData();

private:
	void packPrimaryHeader();
	void packBytes();

	TCtransferFramePrimaryHeader m_primary_header;
	std::vector<char> m_packed_bytes;
};

class AOSframeEncode
{
public:
	AOSframeEncode();
	~AOSframeEncode();
};

#endif	// FRAMEENCODE_H
