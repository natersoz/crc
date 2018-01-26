/**
 * @file crc16.c
 *
 * @cite The table lookup technique was adapted from the algorithm described
 * by Avram Perez, Byte-wise CRC Calculations, IEEE Micro 3, 40 (1983).
 */

#include "crc16.h"

uint16_t crc16_calc(uint16_t const *crc_table, uint16_t crc16, void const *buffer, size_t length)
{
	uint8_t const *buffer8 = (uint8_t *) buffer;
	uint8_t const byte_mask = 0xffu;

	for (size_t iter = 0; iter < length; ++iter)
	{
		uint8_t const table_index = ((crc16 >> 8) ^ buffer8[iter]) & byte_mask;
		crc16 = (crc16 << 8) ^ crc_table[table_index];
	}

	return crc16;
}

