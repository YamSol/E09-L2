
DEVICE=atmega328p
#DEVICE=atmega328

# all: elf_compile hex_compile upload clean
all: elf_compile hex_compile

elf_compile:
	avr-gcc -mmcu=$(DEVICE) -Wall -Os -o o.elf ./src/main.c

hex_compile:
	avr-objcopy -O ihex -R .eeprom o.elf o.hex

upload:
	avrdude -p $(DEVICE) -c stk500v1 -P /dev/ttyUSB0 -b 115200 -v -V -F -U flash:w:o.hex

clean:
	rm -r o.elf o.hex
