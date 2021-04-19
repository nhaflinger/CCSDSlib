#ifndef ENDIAN_H
#define ENDIAN_H

#include <stdint.h>
#include <string.h>

inline uint64_t _byteswap_64(uint64_t const x)
{
	uint8_t data[8] = {};
	memcpy(&data, &x, sizeof(data));

	return ((uint64_t)data[7] << 0)
		| ((uint64_t)data[6] << 8)
		| ((uint64_t)data[5] << 16)
		| ((uint64_t)data[4] << 24)
		| ((uint64_t)data[3] << 32)
		| ((uint64_t)data[2] << 40)
		| ((uint64_t)data[1] << 48)
		| ((uint64_t)data[0] << 56);
}

inline int32_t _byteswap_32(int32_t const x)
{
	int8_t data[4] = {};
	memcpy(&data, &x, sizeof(data));

	return ((int32_t)data[3] << 0)
		| ((int32_t)data[2] << 8)
		| ((int32_t)data[1] << 16)
		| ((int32_t)data[0] << 24);
}

inline uint16_t _byteswap_16(uint16_t const x)
{
	uint8_t data[2] = {};
	memcpy(&data, &x, sizeof(data));

	return ((uint16_t)data[1] << 0)
		| ((uint16_t)data[0] << 8);
}

inline float _byteswap_float(const float inFloat)
{
	float retval;
	char* floatToConvert = (char*)&inFloat;
	char* returnFloat = (char*)&retval;

	// swap the bytes into a temporary buffer
	returnFloat[0] = floatToConvert[3];
	returnFloat[1] = floatToConvert[2];
	returnFloat[2] = floatToConvert[1];
	returnFloat[3] = floatToConvert[0];

	return retval;
}

inline double _byteswap_double(const double inDouble)
{
	double retval;
	char* doubleToConvert = (char*)&inDouble;
	char* returnDouble = (char*)&retval;

	// swap the bytes into a temporary buffer
	returnDouble[0] = doubleToConvert[7];
	returnDouble[1] = doubleToConvert[6];
	returnDouble[2] = doubleToConvert[5];
	returnDouble[3] = doubleToConvert[4];
	returnDouble[4] = doubleToConvert[3];
	returnDouble[5] = doubleToConvert[2];
	returnDouble[6] = doubleToConvert[1];
	returnDouble[7] = doubleToConvert[0];

	return retval;
}

#endif	// ENDIAN_H