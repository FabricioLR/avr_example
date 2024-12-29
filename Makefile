CC=avr-gcc
CFLAGS= -Wall -Wextra -Os -DF_CPU=16000000UL -mmcu=atmega328p

PROGRAM_NAME = blink

all: $(PROGRAM_NAME)

# Compile and build the program for Atmega328P
$(PROGRAM_NAME):
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME).elf $(PROGRAM_NAME).c
	avr-objcopy -O ihex -R .eeprom $(PROGRAM_NAME).elf $(PROGRAM_NAME).hex

# Upload the built program (hex file) to Atmega328P using USBasp
upload: $(PROGRAM_NAME)
	avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -U flash:w:$(PROGRAM_NAME).hex

# Remove build directory with all built files
clean:
	rm -rf $(PROGRAM_NAME).hex

serial-w:
	echo -ne "\xFF" > /dev/ttyUSB0

serial-r:
	cat -v < /dev/ttyUSB0