#ifndef CRCCHECKSUM_H
#define CRCCHECKSUM_H

#include <stdint.h>


class CRCchecksum
{
public:
	CRCchecksum();
	~CRCchecksum();

	uint16_t crc16_checksum(uint16_t seed, unsigned char* buf, int len);
	uint32_t crc32_checksum(uint32_t seed, const void* buf, int len);

private:
	uint32_t crc32_for_byte(uint32_t r);
};

#endif	// CRCCHECKSUM_H
