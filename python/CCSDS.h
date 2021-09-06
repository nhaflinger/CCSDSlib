#ifndef CCSDS_H
#define CCSDS_H

#define PRIMARY_HEADER_OFFSET 6
#define SECONDARY_HEADER_OFFSET 6

struct CCSDSprimaryHeader 
{
	unsigned int packet_version : 3; 
	unsigned int packet_type : 1;
	unsigned int sec_hdr_flag : 1;
	unsigned int apid : 11;
	unsigned int seq_flags : 2;
	unsigned int packet_count_or_name : 14;
	unsigned int packet_length : 16;
};

enum PrimaryHeaderMasks					// masks are 16 bit wide
{
	PACKET_VERSION_MASK = 0xE000,		// first 3 bits
	PACKET_TYPE_MASK = 0x1000,			// next bit
	SEQ_HDR_FLAG_MASK = 0x800,			// next bit
	APID_MASK = 0x7FF,					// next 11 bits
	SEQ_FLAGS_MASK = 0xC000,			// first 2 bits 
	PACKET_COUNT_MASK = 0x3FFF,			// next 14 bits
	PACKET_LENGTH_MASK = 0xFFFF			// first 16 bits
};

struct CCSDSsecondaryHeader
{
	unsigned int seconds : 32;
	unsigned int subseconds : 16;
};

enum SecondaryHeaderMasks
{
	SECONDS_MASK = 0xFFFFFFFF,			// first 32 bits
	SUBSECONDS_MASK = 0xFFFF			// first 16 bits
};

#define FRAME_PRIMARY_HEADER_OFFSET 4

struct CCSDSframePrimaryHeader
{
	unsigned int frame_version : 2;
	unsigned int bypass_flag : 1;
	unsigned int ctrl_cmd_flag : 1;
	unsigned int rsvd_spare : 2;
	unsigned int spacecraft_id : 10;
	unsigned int virt_channel_id : 6;
	unsigned int frame_length : 10;
	unsigned int frame_seq_number : 8;
};

enum FramePrimaryHeaderMasks	// masks are 16 bit wide
{
	FRAME_VERSION_MASK = 0xC000,		// first 2 bits
	BYPASS_FLAG_MASK = 0x2000,			// next bit
	CTRL_CMD_FLAG_MASK = 0x10000,		// next bit
	RSVD_SPARE_MASK = 0xC00,			// next 2 bits
	SPACECRAFT_ID_MASK = 0x3FF,			// next 10 bits 
	VIRT_CHANNEL_ID_MASK = 0xFC00,		// first 6 bits
	FRAME_LENGTH_MASK = 0x3FF,			// next 10 bits
	FRAME_SEQ_NUMBER_MASK = 0xFF00		// first 8 bits
};

#define COMMAND_HEADER_OFFSET 12
#define COMMAND_OPCODE 4
#define COMMAND_DEVICE_NUMBER 1
#define COMMAND_DATA_STRING 23
#define COMMAND_CRC32 4

struct CCSDScommandHeader
{
	unsigned int packet_type : 32;
	unsigned int packet_seq_count : 32;
	unsigned int packet_length : 32;
};

struct CCSDScommandData
{
	unsigned int command_opcode : 32;
	unsigned int device_number : 8;
	char command_data[23];
	unsigned int crc32_checksum : 32;
};

enum CCSDScommandMasks
{
	OPCODE_PARAM_MASK = 0xFFFFFFFF,		// first 32 bits
	DEV_NUM_MASK = 0xFF00,				// first 8 bits
};

#endif	// CCSDS_H