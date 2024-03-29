
OPT = -Os
LTO = -flto -ffat-lto-objects

BUILD_DIR = build

# WHY NOT? src/ch32v00x_core.c

C_SOURCES = \
src/adc.c \
src/dbgmcu.c \
src/dma.c \
src/exti.c \
src/flash.c \
src/gpio.c \
src/i2c.c \
src/it.c \
src/iwdg.c \
src/nvic.c \
src/opa.c \
src/pwr.c \
src/rcc.c \
src/spi.c \
src/system.c \
src/tim.c \
src/usart.c \
src/wwdg.c \

NO_LTO_C_SOURCES = \
src/libgloss/close.c \
src/libgloss/getpid.c \
src/libgloss/inbyte.c \
src/libgloss/isatty.c \
src/libgloss/lseek.c \
src/libgloss/print.c \
src/libgloss/read.c \
src/libgloss/sbrk.c \
src/libgloss/unlink.c \
src/libgloss/fstat.c \
src/libgloss/kill.c \
src/libgloss/open.c \
src/libgloss/outbyte.c \
src/libgloss/putnum.c \
src/libgloss/stat.c \
src/libgloss/write.c \


# ASM sources
AS_SOURCES =  \
src/startup.S \

TARGET := riscv-none-elf-

CC = $(TARGET)gcc
AR = $(TARGET)gcc-ar
AS = $(TARGET)gcc -x assembler-with-cpp
CP = $(TARGET)objcopy
SZ = $(TARGET)size
ST = $(TARGET)strip

CPU = -march=rv32ec_zicsr -mabi=ilp32e -msmall-data-limit=8

MCU = $(CPU) $(FPU) $(FLOAT-ABI)

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-Iinclude \

# compile gcc flags
ASFLAGS = $(MCU) $(AS_INCLUDES) $(OPT) $(LTO) -Wall -fdata-sections -ffunction-sections
CFLAGS = $(MCU) $(C_INCLUDES) $(OPT) $(LTO) -Wall -fdata-sections -ffunction-sections

NO_LTO_ASFLAGS = $(MCU) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
NO_LTO_CFLAGS = $(MCU) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# FIXME non penso serva
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

# default action: build all
all: $(BUILD_DIR)/libwch.a $(BUILD_DIR)/startup.o

LTO_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
NO_LTO_OBJECTS = $(addprefix $(BUILD_DIR)/no-lto-,$(notdir $(NO_LTO_C_SOURCES:.c=.o)))
OBJECTS = $(LTO_OBJECTS) $(NO_LTO_OBJECTS)

vpath %.c $(sort $(dir $(C_SOURCES) $(NO_LTO_C_SOURCES)))
vpath %.S $(sort $(dir $(AS_SOURCES)))

$(BUILD_DIR)/no-lto-%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(NO_LTO_CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/libwch.a: $(OBJECTS) Makefile
	$(AR) rcs $@ $(OBJECTS)
	
$(BUILD_DIR):
	mkdir $@

.PHONY: install clean

install: install-lib install-headers install-scripts

install-strip: install-strip-lib install-headers install-scripts

install-strip-lib: $(BUILD_DIR)/libwch.a
	install -Ds --strip-program="$(ST)" -m 644 $(BUILD_DIR)/libwch.a $(DESTDIR)/usr/riscv-none-elf/lib/libwch.a
	install -Ds --strip-program="$(ST)" -m 644 $(BUILD_DIR)/ch32v00x_startup.o $(DESTDIR)/usr/riscv-none-elf/lib/ch32v00x_crt0.o

install-lib: $(BUILD_DIR)/libwch.a
	install -D -m 644 $(BUILD_DIR)/libwch.a $(DESTDIR)/usr/riscv-none-elf/lib/libwch.a
	install -D -m 644 $(BUILD_DIR)/startup.o $(DESTDIR)/usr/riscv-none-elf/lib/ch32v00x_crt0.o

install-scripts:
	install -D -m 644 scripts/ch32v00x.specs $(DESTDIR)/usr/riscv-none-elf/lib/ch32v00x.specs
	install -D -m 644 scripts/ch32v00x.ld $(DESTDIR)/usr/riscv-none-elf/lib/ch32v00x.ld

install-headers:
	# I could have written a proper glob, but I didn't wanted to: as much as I don't
	# like them, I think autotools are the way to go here to support multilib properly
	# (if it will be ever needed).
	install -D -m 644 include/ch32v00x/device.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/device.h
	install -D -m 644 include/ch32v00x/adc.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/adc.h
	install -D -m 644 include/ch32v00x/core.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/core.h
	install -D -m 644 include/ch32v00x/dbgmcu.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/dbgmcu.h
	install -D -m 644 include/ch32v00x/dma.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/dma.h
	install -D -m 644 include/ch32v00x/exti.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/exti.h
	install -D -m 644 include/ch32v00x/flash.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/flash.h
	install -D -m 644 include/ch32v00x/gpio.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/gpio.h
	install -D -m 644 include/ch32v00x/i2c.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/i2c.h
	install -D -m 644 include/ch32v00x/iwdg.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/iwdg.h
	install -D -m 644 include/ch32v00x/nvic.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/nvic.h
	install -D -m 644 include/ch32v00x/opa.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/opa.h
	install -D -m 644 include/ch32v00x/pwr.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/pwr.h
	install -D -m 644 include/ch32v00x/rcc.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/rcc.h
	install -D -m 644 include/ch32v00x/spi.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/spi.h
	install -D -m 644 include/ch32v00x/sysclk.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/sysclk.h
	install -D -m 644 include/ch32v00x/tim.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/tim.h
	install -D -m 644 include/ch32v00x/usart.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/usart.h
	install -D -m 644 include/ch32v00x/wwdg.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x/wwdg.h

clean:
	-rm -fR $(BUILD_DIR)
