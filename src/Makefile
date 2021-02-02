# Makefile for programming the ATtiny85 with micronucleus

DEVICE      = attiny85
CLOCK      = 16500000L
PROGRAMMER = ../micronucleus/2.0a4/launcher 
OBJECTS    = main.o
# for ATTiny85
# see http://www.engbedded.com/fusecalc/
FUSES = -U lfuse:w:0xf1:m -U hfuse:w:0xdf:m -U efuse:w:0xfe:m 

# Tune the lines below only if you know what you are doing:
PROG = $(PROGRAMMER) -cdigispark --timeout 60
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(PROG)  -Uflash:w:main.hex:i

fuse:
	$(PROG) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	$(PROG)  -Uflash:w:main.hex:i

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c
