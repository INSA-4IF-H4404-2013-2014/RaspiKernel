OPTIONSFILE = ../makeOptions.gitlocal
PARSERFILE = ../.common_parser.mk
include ../common.mk

APP_NAME=$(notdir $(shell pwd | sed 's/ /\\/g'))

.PHONY: release send

send:
	@make -C ../ send

ifndef REMOTE_USERNAME
remote sdcopy umount:
	$(error "Please first set REMOTE_USERNAME variable in $(OPTIONSFILE)!")

else

remote:
	$(CMD_ECHO) "# remote compiling..."
	@ssh $(REMOTE) 'make --no-print-directory -C $(REMOTE_FOLDER)/$(APP_NAME)'
	$(CMD_ECHO)

ifndef SDCARD
sdcopy umount:
	$(error "Please first set SDCARD variable in $(OPTIONSFILE)!")
else
sdcopy:
	$(CMD_ECHO) "# deploying kernel.img on SDCARD..."
	@scp $(REMOTE):$(REMOTE_FOLDER)/$(APP_NAME)/$(BUILD_DIR)kernel.img $(SDCARD)
	$(CMD_ECHO)

umount:
	$(CMD_ECHO) "# unmounting SDCARD..."
	@umount $(SDCARD)
	$(CMD_ECHO)
endif

endif


deploy: send remote sdcopy umount
