
DEVICE=atmega328p
# DEVICE=atmega328

FILE=main.c
# FILE=main2.c

# all: elf_compile hex_compile upload clean
all: create_build_folder elf_compile hex_compile

create_build_folder:
	mkdir -p ./build

elf_compile:
	avr-gcc -mmcu=$(DEVICE) -Wall -Os -o ./build/o.elf $(FILE)

hex_compile:
	avr-objcopy -O ihex -R .eeprom ./build/o.elf ./build/o.hex

upload:
	avrdude -p $(DEVICE) -c stk500v1 -P /dev/ttyUSB0 -b 115200 -v -V -F -U flash:w:o.hex

clean:
	# rm -r o.elf o.hex
	rm -r ./build
