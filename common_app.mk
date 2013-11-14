OPTIONSFILE = ../makeOptions.gitlocal
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
	@ssh $(REMOTE) 'make --no-print-directory -C $(REMOTE_FOLDER)/$(APP_NAME)'

ifndef SDCARD
sdcopy umount:
	$(error "Please first set SDCARD variable in $(OPTIONSFILE)!")
else
sdcopy:
	@scp $(REMOTE):$(REMOTE_FOLDER)/$(APP_NAME)/$(BUILD_DIR)kernel.img $(SDCARD)

umount:
	@umount $(SDCARD)
endif

endif


deploy: send remote sdcopy umount
