
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
all: libwch.a

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

libwch.a: $(OBJECTS) Makefile
	$(AR) rcs $@ $(OBJECTS)
	
$(BUILD_DIR):
	mkdir $@

clean:
	-rm -fR $(BUILD_DIR)
