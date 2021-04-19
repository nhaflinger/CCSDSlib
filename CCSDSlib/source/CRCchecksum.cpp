#ifdef __linux__
//linux code goes here
#elif defined(_WIN32) || defined(WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "CRCchecksum.h"

using namespace std;

CRCchecksum::CRCchecksum()
{
}

CRCchecksum::~CRCchecksum()
{
}

/***********************************************************************
*
* FUNCTION:
* crc16_checksum
*
* INPUTS:
* seed - (uint16_t) initial value of check bits.
* buf - (unsigned char *) pointer to the buffer of
* data over which you wish to generate check
* bits.
* len - (int) number to bytes of data in the buffer.
*
* OUTPUTS:
*
* RETURNS:
* - (uint16_t) the checkbits.
*
* DESCRIPTION:
* This function implements CRC generation with the CCITT SDLC error
* polynomial (X16 + X12 + X5 + 1). You must provide it with an
* initial seed value, a pointer to a data buffer, and the byte length
* of the data buffer. It will return the unsigned 16-bit CRC.
*
* You may use this function to generate a CRC over data in scattered
* storage by making multiple calls to it. Just make sure that you
* pass a seed of 0xFFFF on the first call. On subsequent calls, pass
* a seed containing the return value of the previous call.
*
*/

uint16_t CRCchecksum::crc16_checksum(uint16_t seed, unsigned char* buf, int len)
{
	unsigned short crc;
	unsigned short ch, xor_flag;
	int i, count;
	crc = seed;
	count = 0;
	while (len--)
	{
		ch = buf[count++];
		ch <<= 8;
		for (i = 0; i < 8; i++)
		{
			if ((crc ^ ch) & 0x8000)
			{
				xor_flag = 1;
			}
			else
			{
				xor_flag = 0;
			}
			crc = crc << 1;
			if (xor_flag)
			{
				crc = crc ^ 0x1021;
			}
			ch = ch << 1;
		}
	}
	return (unsigned short)crc;
}

/***********************************************************************
*
* FUNCTION:
* crc32_checksum
*
* INPUTS:
* seed - (uint32_t) initial value of check bits.
* buf - (unsigned char *) pointer to the buffer of
* data over which you wish to generate check bits.
* len - (int) number to bytes of data in the buffer.
*
* OUTPUTS:
*
* RETURNS:
* - (uint32_t) the checkbits.
*
* DESCRIPTION:
* Here is a simple implementation of the commonly used CRC32 checksum using the reverse polynomial 0xEDB88320.
* The algorithm is consistent with setting of all bits in the initial CRC, along with negation of the bit pattern of the final running CRC.
* The code has been tested against the CRC - routines in the PNG specification published by W3C.
* http://home.thep.lu.se/~bjorn/crc/
*
*/

uint32_t CRCchecksum::crc32_for_byte(uint32_t r)
{
	for (int j = 0; j < 8; ++j)
		r = (r & 1 ? 0 : (uint32_t)0xEDB88320L) ^ r >> 1;
	return r ^ (uint32_t)0xFF000000L;
}

uint32_t CRCchecksum::crc32_checksum(uint32_t seed, const void* buf, int len)
{
	uint32_t crc = seed;
	static uint32_t table[0x100];
	if (!*table)
		for (int i = 0; i < 0x100; ++i)
			table[i] = crc32_for_byte(i);
	for (int i = 0; i < len; ++i)
		crc = table[(uint8_t)crc ^ ((uint8_t*)buf)[i]] ^ crc >> 8;

	return crc;
}