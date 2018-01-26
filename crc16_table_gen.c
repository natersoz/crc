/**
 * @file crc16_table_gen.c
 *
 * main() for a program which generates a C language uint16_t[256] table
 * for use in byte-wise CRC-16 calculations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "crc16.h"

static void usage(char const *program_name)
{
    fprintf(stderr, "usage: %s polynomial\n", program_name);
    fprintf(stderr, "\texample: for CRC-16-CCITT use 0x1021\n");
    fprintf(stderr, "\t%s 0x1021\n", program_name);
    fprintf(stderr, "\n");
}

static void crc16_table_print(FILE *fout, uint16_t const *crc16_table, uint16_t crc16_poly)
{
    fprintf(fout, "uint16_t const crc16_table_0x%04x[] = {", crc16_poly);

    for (size_t index = 0; index < 256u; ++index) {
        if (index % 8 == 0) {
            fprintf(fout, "\n\t");
        }
        fprintf(fout, "0x%04x, ", crc16_table[index]);
    }

    fprintf(fout, "\n};");
    fprintf(fout, "\n");
}

int main(int argc, char const **argv)
{
    int error = 0;

    // All zeroes on the polynomial is uninteresting.
    // Use that case as the default.
    uint16_t crc16_poly = 0x0000;

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

    fprintf(stderr, "Using polynomial: 0x%04x\n", crc16_poly);

    if (crc16_poly == 0x0000) {
        usage(argv[0]);                            // Looks like someone forgot their polynomial.
        error = EINVAL;
    }

    uint16_t crc16_table[256];
    crc16_table_init(crc16_table, crc16_poly);
    crc16_table_print(stdout, crc16_table, crc16_poly);

    return error;
}

