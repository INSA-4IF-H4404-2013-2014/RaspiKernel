
#------------------------------------------------------------------------------- FUNCTIONS

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))


#------------------------------------------------------------------------------- CONFIGURATIONS

TARGET = kernel

CC_FLAGS = -Wall -Wextra -Werror -nostdlib -fomit-frame-pointer -mno-apcs-frame -nostartfiles -ffreestanding -g -march=armv6z -marm
AS_FLAGS = -g -march=armv6z

GDB_DEFAULT = gdb/default.gdb


#------------------------------------------------------------------------------- AUTOMATED

THIS = $(lastword $(MAKEFILE_LIST))
C_FILES = $(call rwildcard,./,*.c)
S_FILES = $(call rwildcard,./,*.s)
D_FILES = $(call rwildcard,./,*.d)

SD_CARD_DIR = SD_Card/

BUILD_DIR = build/
BUILD_TARGET = $(addprefix $(BUILD_DIR), $(TARGET))
BUILD_OBJS = $(addprefix $(BUILD_DIR), $(addsuffix .o,$(notdir $(S_FILES) $(C_FILES))))

# read QEMU_MACHINE from qemu-machine.gitlocal
ifeq ($(wildcard qemu-machine.gitlocal),)
    QEMU_MACHINE = raspi
else
    QEMU_MACHINE = $(shell sed -n 1p qemu-machine.gitlocal)
endif



#------------------------------------------------------------------------------- COMMANDS

HIDE_CMD =@
BUILD_PREFIX ?= $(HIDE_CMD)arm-none-eabi-

CMD_LD = $(BUILD_PREFIX)ld
CMD_AS = $(BUILD_PREFIX)as
CMD_CC = $(BUILD_PREFIX)gcc
CMD_LD = $(BUILD_PREFIX)ld
CMD_OBJDUMP = $(BUILD_PREFIX)objdump
CMD_OBJCOPY = $(BUILD_PREFIX)objcopy

CMD_CP = $(HIDE_CMD)cp
CMD_ECHO = @echo
CMD_MKDIR = $(HIDE_CMD)mkdir
CMD_RM = $(HIDE_CMD)rm


#------------------------------------------------------------------------------- STATIC RULES

.PHONY: update clean full run gdb

update : $(BUILD_DIR) $(BUILD_TARGET).hex $(BUILD_TARGET).bin $(BUILD_TARGET).img
	$(CMD_ECHO) "# build finished"

clean :
	$(CMD_RM) -rf $(BUILD_DIR)

full : clean update

run : $(GDB_DEFAULT)

emu : update
	$(CMD_ECHO) "# running <$(BUILD_TARGET).elf> ($(QEMU_MACHINE))..."
	@qemu-system-arm -kernel $(BUILD_TARGET).elf -cpu arm1176 -m 512 -M $(QEMU_MACHINE) -nographic -no-reboot -serial stdio -append "rw earlyprintk loglevel=8 panic=120 keep_bootcon rootwait dma.dmachans=0x7f35 bcm2708_fb.fbwidth=1024 bcm2708_fb.fbheight=768 bcm2708.boardrev=0xf bcm2708.serial=0xcad0eedf smsc95xx.macaddr=B8:27:EB:D0:EE:DF sdhci-bcm2708.emmc_clock_freq=100000000 vc_mem.mem_base=0x1c000000 vc_mem.mem_size=0x20000000  dwc_otg.lpm_enable=0 kgdboc=ttyAMA0,115200 console=ttyS0 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline rootwait" -S -s #-device usb-kbd -device usb-mouse
	@reset

gdb : update
	$(CMD_ECHO) "# running gdb..."
	arm-none-eabi-gdb $(BUILD_TARGET).elf -x gdbinit.gdb


#------------------------------------------------------------------------------- DYNAMIC RULES

$(BUILD_DIR):
	$(CMD_MKDIR) $(BUILD_DIR)


#------------------------------------------------------------------------------- DYNAMIC RULES

.SECONDEXPANSION:

$(BUILD_DIR)%.c.o: $$(call rwildcard,./,*%.c) $(THIS)
	$(CMD_ECHO) "# file <$<>"
	$(CMD_CC) $(CC_FLAGS) -x c -S -o $(BUILD_DIR)$<.s -MMD -MQ $@ -MF $(patsubst %.o,%.d, $@) $<
	$(CMD_AS) $(AS_FLAGS) -o $@ $(BUILD_DIR)$<.s
	$(CMD_RM) -f $(BUILD_DIR)$<.s

$(BUILD_DIR)%.s.o: $$(call rwildcard,./,*%.s) $(THIS)
	$(CMD_ECHO) "# file <$<>"
	$(CMD_AS) $(AS_FLAGS) $< -o $@

%.gdb : update
	@qemu-system-arm -kernel $(BUILD_TARGET).elf -cpu arm1176 -m 512 -M $(QEMU_MACHINE) -nographic -no-reboot -serial stdio -append "rw earlyprintk loglevel=8 panic=120 keep_bootcon rootwait dma.dmachans=0x7f35 bcm2708_fb.fbwidth=1024 bcm2708_fb.fbheight=768 bcm2708.boardrev=0xf bcm2708.serial=0xcad0eedf smsc95xx.macaddr=B8:27:EB:D0:EE:DF sdhci-bcm2708.emmc_clock_freq=100000000 vc_mem.mem_base=0x1c000000 vc_mem.mem_size=0x20000000  dwc_otg.lpm_enable=0 kgdboc=ttyAMA0,115200 console=ttyS0 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline rootwait" -S -s > $(BUILD_DIR)qemu.stdout 2> $(BUILD_DIR)qemu.stderr & \
	QEMU_PID=$$!;                                                           \
	echo "# running emulator <$(BUILD_TARGET).elf> (-M $(QEMU_MACHINE)) : PID = $$QEMU_PID" ;\
	echo "# running gdb ($@)..." ;                                          \
	arm-none-eabi-gdb $(BUILD_TARGET).elf -x $@ ;                           \
	echo "# killing emulator" ;                                             \
	kill -9 $$QEMU_PID;


#------------------------------------------------------------------------------- TARGET RULES

$(BUILD_TARGET).elf : memmap $(BUILD_OBJS)
	$(CMD_ECHO) "# file <$@>"
	$(CMD_LD) $(BUILD_OBJS) -T memmap -o $@
	$(CMD_OBJDUMP) -D $@ > $(BUILD_TARGET).list

$(BUILD_TARGET).bin : $(BUILD_TARGET).elf
	$(CMD_ECHO) "# file <$@>"
	$(CMD_OBJCOPY) $< -O binary $@

$(BUILD_TARGET).hex : $(BUILD_TARGET).elf
	$(CMD_ECHO) "# file <$@>"
	$(CMD_OBJCOPY) $< -O ihex $@

$(BUILD_TARGET).img : $(BUILD_TARGET).elf
	$(CMD_ECHO) "# file <$@>"
	$(CMD_OBJCOPY) $< -O binary $@


#------------------------------------------------------------------------------- INCLUDES

-include $(D_FILES)
