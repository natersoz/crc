###
# crc16/Makefile
###

all:
	Make -f Makefile.crc16_test		$@
	Make -f Makefile.crc16_table_gen	$@

clean:
	Make -f Makefile.crc16_test		$@
	Make -f Makefile.crc16_table_gen	$@

relink:
	Make -f Makefile.crc16_test		$@
	Make -f Makefile.crc16_table_gen	$@


