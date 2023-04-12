
OPT = -Os -flto -ffat-lto-objects

BUILD_DIR = build

# WHY NOT? src/ch32v00x_core.c
C_SOURCES = \
src/ch32v00x_adc.c \
src/ch32v00x_dbgmcu.c \
src/ch32v00x_debug.c \
src/ch32v00x_dma.c \
src/ch32v00x_exti.c \
src/ch32v00x_flash.c \
src/ch32v00x_gpio.c \
src/ch32v00x_i2c.c \
src/ch32v00x_it.c \
src/ch32v00x_iwdg.c \
src/ch32v00x_misc.c \
src/ch32v00x_opa.c \
src/ch32v00x_pwr.c \
src/ch32v00x_rcc.c \
src/ch32v00x_spi.c \
src/ch32v00x_system.c \
src/ch32v00x_tim.c \
src/ch32v00x_usart.c \
src/ch32v00x_wwdg.c \


# ASM sources
ASM_SOURCES =  \
src/ch32v00x_startup.S \

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
ASFLAGS = $(MCU) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# FIXME non penso serva
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

LIBS = -lc -lm -lnosys
LIBDIR = 

# default action: build all
all: $(BUILD_DIR)/libwch.a

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

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
	install -D -m 644 $(BUILD_DIR)/ch32v00x_startup.o $(DESTDIR)/usr/riscv-none-elf/lib/ch32v00x_crt0.o

install-scripts:
	install -D -m 644 scripts/ch32v00x.specs $(DESTDIR)/usr/riscv-none-elf/lib/ch32v00x.specs
	install -D -m 644 scripts/ch32v00x.ld $(DESTDIR)/usr/riscv-none-elf/lib/ch32v00x.ld

install-headers:
	# I could have written a proper glob, but I didn't wanted to: as much as I don't
	# like them, I think autotools are the way to go here to support multilib properly
	# (if it will be ever needed).
	install -D -m 644 include/ch32v00x.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x.h
	install -D -m 644 include/ch32v00x_adc.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_adc.h
	install -D -m 644 include/ch32v00x_core.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_core.h
	install -D -m 644 include/ch32v00x_dbgmcu.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_dbgmcu.h
	install -D -m 644 include/ch32v00x_debug.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_debug.h
	install -D -m 644 include/ch32v00x_dma.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_dma.h
	install -D -m 644 include/ch32v00x_exti.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_exti.h
	install -D -m 644 include/ch32v00x_flash.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_flash.h
	install -D -m 644 include/ch32v00x_gpio.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_gpio.h
	install -D -m 644 include/ch32v00x_i2c.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_i2c.h
	install -D -m 644 include/ch32v00x_iwdg.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_iwdg.h
	install -D -m 644 include/ch32v00x_misc.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_misc.h
	install -D -m 644 include/ch32v00x_opa.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_opa.h
	install -D -m 644 include/ch32v00x_pwr.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_pwr.h
	install -D -m 644 include/ch32v00x_rcc.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_rcc.h
	install -D -m 644 include/ch32v00x_spi.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_spi.h
	install -D -m 644 include/ch32v00x_system.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_system.h
	install -D -m 644 include/ch32v00x_tim.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_tim.h
	install -D -m 644 include/ch32v00x_usart.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_usart.h
	install -D -m 644 include/ch32v00x_wwdg.h $(DESTDIR)/usr/riscv-none-elf/include/ch32v00x_wwdg.h


clean:
	-rm -fR $(BUILD_DIR)
