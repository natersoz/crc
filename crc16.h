/**
 * @file crc16.h
 *
 * @cite The table lookup technique was adapted from the algorithm described
 * by Avram Perez, Byte-wise CRC Calculations, IEEE Micro 3, 40 (1983).
 *
 * For a polynomial, generate a table:
 *     uint16_t crc16_pppp_table[256];
 * where pppp represents the polynomial.
 * @note The x^16 coefficient is always '1' and is not represented in the polynomial.
 */

#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/// The typical CRC-16 seed value.
#define CRC16_SEED	((uint16_t) 0xffffu)

/**
 * The generic CRC-16 calculator using a table based byte-wise operator.
 * @note This implementation does not reflect the input data nor does it reverse the polynomial order.
 *
 * @param crc_table A const array of 256 unsigned 16 bit integer values generated specifically for the
 * 16 bit CRC polynomial.
 * @param crc16 The crc16 value to load into the calculation. The initial seed is typically the value 0xffff.
 * When chaining blocks of crc16 calculations the output of one block is the seed value for the next block.
 * @param buffer The usder supplied buffer to calculate the CRC-16 against.
 * @param length The number of bytes in the user supplied buffer.
 *
 * @return uint16_t The resulting CRC-16 value. This value can be used to seed the block in the chain if necessary.
 */
uint16_t crc16_calc(uint16_t const *crc_table, uint16_t crc16, void const *buffer, size_t length);

/**
 * Calculate the CRC-16-CCITT using a table bite-wise implemenentation
 * @note This implementation does not reflect the input data nor does it reverse the polynomial order.
 *
 * @param crc16 The crc16 value to load into the calculation. The initial seed is typically the value 0xffff.
 * When chaining blocks of crc16 calculations the output of one block is the seed value for the next block.
 * @param buffer The usder supplied buffer to calculate the CRC-16 against.
 * @param length The number of bytes in the user supplied buffer.
 *
 * @return uint16_t The resulting CRC-16 value. This value can be used to seed the block in the chain if necessary.
 */
uint16_t crc16_ccitt(uint16_t crc16, void const *buffer, size_t length);

/**
 * Initialize a CRC-16 table based on a polynomial. The resulting table can be used for
 * byte-wise CRC-16 calculations.
 *
 * @param crc_table A 256 byte array of uint16_t entries to fill. Array bounds are not checked.
 * @param crc16_poly The CRC-16 polynomial used to initialize the table.
 */
void crc16_table_init(uint16_t *crc_table, uint16_t crc16_poly);

#ifdef __cplusplus
}
#endif

