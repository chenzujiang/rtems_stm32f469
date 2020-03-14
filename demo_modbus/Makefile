#
#  $Id: Makefile,v 1.1.2.1 2009/05/18 17:50:53 joel Exp $
#
#  $(warning $(C_O_FILES))

TARGET_PROJECT_NAME=modbus
TARGET_PROJECT_PATH=$(shell pwd)
PGM=${ARCH}/$(TARGET_PROJECT_NAME).exe

MANAGERS=all

# C source names, if any, go here -- minus the .c
# user
C_FILES = init.c
C_FILES += user/modbus/modbus_regs.c
C_FILES += user/tasks/task_modbus.c
C_FILES += user/tasks/task_status.c
# startup
C_FILES += startup/system_stm32f407.c
# bsp
C_FILES += bsp/delay/delay.c
C_FILES += bsp/modbus/portevent.c
C_FILES += bsp/modbus/portother.c
C_FILES += bsp/modbus/portserial.c
C_FILES += bsp/modbus/porttimer.c
# freemodbus
C_FILES += libraries/modbus/ascii/mbascii.c
C_FILES += libraries/modbus/functions/mbfunccoils.c
C_FILES += libraries/modbus/functions/mbfuncdiag.c
C_FILES += libraries/modbus/functions/mbfuncdisc.c
C_FILES += libraries/modbus/functions/mbfuncholding.c
C_FILES += libraries/modbus/functions/mbfuncinput.c
C_FILES += libraries/modbus/functions/mbfuncother.c
C_FILES += libraries/modbus/functions/mbutils.c
C_FILES += libraries/modbus/rtu/mbcrc.c
C_FILES += libraries/modbus/rtu/mbrtu.c
C_FILES += libraries/modbus/tcp/mbtcp.c
C_FILES += libraries/modbus/mb.c

C_O_FILES=$(addprefix ${ARCH}/, $(notdir $(C_FILES:%.c=${ARCH}/%.o)))

DOCTYPES=
DOCS=$(DOCTYPES:%=$(TARGET_PROJECT_NAME).%)

SRCS=$(DOCS) $(C_FILES)
OBJS=$(C_O_FILES)

PRINT_SRCS=$(DOCS)

include $(RTEMS_MAKEFILE_PATH)/Makefile.inc
include $(RTEMS_CUSTOM)
include $(PROJECT_ROOT)/make/leaf.cfg

#
# (OPTIONAL) Add local stuff here using +=
#

CFLAGS += -I./
CFLAGS += -I./libraries/modbus/include
CFLAGS += -I./libraries/modbus/ascii
CFLAGS += -I./libraries/modbus/rtu
CFLAGS += -I./libraries/modbus/tcp
CFLAGS += -I./bsp/modbus

CPPFLAGS +=

LDFLAGS += -Wl,--gc-sections

#
# Add your list of files to delete here.  The config files
# already know how to delete some stuff, so you may want
# to just run 'make clean' first to see what gets missed.
# 'make clobber' already includes 'make clean'
#

CLEAN_ADDITIONS += ${TARGET_PROJECT_PATH}/target
CLOBBER_ADDITIONS +=

all: ${ARCH} $(SRCS) $(PGM) $(OBJS)

$(foreach each_obj_files, $(OBJS), $(eval $${ARCH}/$(notdir $(each_obj_files)):$(filter %$(basename $(notdir $(each_obj_files))).c,${SRCS});${COMPILE.c} $(AM_CPPFLAGS) $(AM_CFLAGS) -o $$@ $$<))

${PGM}: ${ARCH} $(OBJS) $(LINK_FILES)
	$(make-exe)

# Install the program(s), appending _g or _p as appropriate.
# for include files, just use $(INSTALL)
install:
	$(shell mkdir -p target)
	$(INSTALL_VARIANT) -m 555 ${PGM} ${TARGET_PROJECT_PATH}/target/$(TARGET_PROJECT_NAME).elf
	$(OBJCOPY) -O binary ${TARGET_PROJECT_PATH}/target/$(TARGET_PROJECT_NAME).elf ${TARGET_PROJECT_PATH}/target/$(TARGET_PROJECT_NAME).bin
	$(OBJCOPY) -O ihex ${TARGET_PROJECT_PATH}/target/$(TARGET_PROJECT_NAME).elf ${TARGET_PROJECT_PATH}/target/$(TARGET_PROJECT_NAME).hex

# flash to mcu
flash: install
	st-flash --reset write ${TARGET_PROJECT_PATH}/target/$(TARGET_PROJECT_NAME).bin 0x08000000