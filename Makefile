CFLAGS  ?=  -W -Wall -Wextra -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion \
            -g3 -Os -ffunction-sections -fdata-sections \
            -I. -Icore -Imcu \
            -mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 $(EXTRA_CFLAGS)

LDFLAGS ?=  -Tlink.ld -nostartfiles -nostdlib --specs=nano.specs -lc -lgcc \
            -Wl,--gc-sections -Wl,-Map=$@.map

SOURCES =   ./src/main.c \
            ./core/startup.c

build: firmware.elf

firmware.elf: $(SOURCES)
	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

flash: firmware.bin
	STM32_Programmer_CLI -c port=SWD mode=UR -w firmware.bin 0x08000000 -v -rst

clean: 
	rm -rf firmware.*