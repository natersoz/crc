/**
 * @file crc16_table_init
 */

#include <stdbool.h>
#include "crc16.h"

void crc16_table_init(uint16_t *crc16_table, uint16_t crc16_poly)
{
	for (uint16_t i = 0;  i < 256u;  i++)
	{
		uint16_t crc16 = (i << 8u);

		for (uint16_t j = 0;  j < 8u;  j++)
		{
			uint16_t const msb16 = 0x8000u;
			bool const msb_set = (crc16 & msb16)? true : false;
			crc16 <<= 1u;

			if (msb_set)
			{
				crc16 ^= crc16_poly;
			}
		}

		crc16_table[i] = crc16;
	}
}

#if 0
void gen_crc_table()
/* generate the table of CRC remainders for all possible bytes */
{
    for(uint32_t i = 0;  i < 256;  i++)
    {
        uint32_t crc_accum = (i << 24);
        for(uint32_t j = 0;  j < 8;  j++)
        {
            if (crc_accum & 0x80000000UL)
            {
                crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
            }
            else
            {
                crc_accum = (crc_accum << 1);
            }
        }
        crc_table[i] = crc_accum;
    }
}
#endif
