OPTIONSFILE = ../makeOptions.gitlocal
include ../common.mk

APP_NAME=$(notdir $(shell pwd | sed 's/ /\\/g'))

.PHONY: release send

send:
	@make -C ../ send

remote:
	@ssh $(REMOTE) 'make -C $(REMOTE_FOLDER)/$(APP_NAME)'

release:
	@scp $(REMOTE):$(REMOTE_FOLDER)/$(APP_NAME)/$(BUILD_DIR)kernel.img $(SDCARD)

umount:
	@umount $(SDCARD)

autorelease: send remote release umount
