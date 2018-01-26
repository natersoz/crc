/**
 * @file crc16_test.cc
 *
 * Test the C implementation of CRC-16 against the boost library.
 */

#include "crc16.h"

#include <boost/crc.hpp>      // for boost::crc_basic, boost::crc_optimal
#include <boost/cstdint.hpp>  // for boost::uint16_t

#include <algorithm>          // for std::for_each
#include <cassert>            // for assert
#include <cstddef>            // for std::size_t
#include <iostream>           // for std::cout
#include <ostream>            // for std::endl

// All zeroes on the polynomial is uninteresting.
// Use that case as the default.
static uint16_t crc16_poly = 0x0000;

// This is "123456789" in ASCII
// For the polynomial 0x1021 the expected result is 0x29b1.
uint8_t const  test_data[] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39 };
std::size_t const   test_data_length = sizeof(test_data) / sizeof(test_data[0]);

static void usage(char const *program_name)
{
    fprintf(stderr, "usage: %s polynomial\n", program_name);
    fprintf(stderr, "\texample: for CRC-16-CCITT use 0x1021\n");
    fprintf(stderr, "\t%s 0x1021\n", program_name);
    fprintf(stderr, "\n");
}

int main(int argc, char const * const * const argv)
{
    int error = 0;

    for (int argv_index = 0; argv_index < argc; ++argv_index) {
        if (*argv[argv_index] == '-') {      // Treat dash as an option.
            switch (argv[argv_index][1]) {   // Parse options.
            default:
                fprintf(stderr, "error: unknown argument: '%s'\n", argv[argv_index]);
                usage(argv[0]);
                error = EINVAL;
                break;
            }
        } else {
            // Treat the 'bare' argument as the polynomial.
            crc16_poly = (uint16_t) strtoul(argv[argv_index], NULL, 0);
        }
    }

    fprintf(stdout, "Using polynomial: 0x%04x\n", crc16_poly);
    if (crc16_poly == 0x0000) {
        usage(argv[0]);
    }

    // Simulate CRC-16-CCITT
    boost::crc_basic<16>  crc_ccitt1(crc16_poly, 0xFFFF, 0, false, false);
    crc_ccitt1.process_bytes(test_data, test_data_length);
    uint16_t const result1 = crc_ccitt1.checksum();

    uint16_t crc_table[256];
    crc16_table_init(crc_table, crc16_poly);
    uint16_t const result2 = crc16_calc(crc_table, CRC16_SEED, test_data, test_data_length);

    bool const success = (result1 == result2);

    fprintf(stdout, "results: 0x%04x, 0x%04x, %s\n", result1, result2, success? "PASS" : "FAIL");

    return success? 0 : -1;
}

