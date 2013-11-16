OPTIONSFILE = ../makeOptions.gitlocal
PARSERFILE = ../.common_parser.mk
include $(PARSERFILE)

APP_NAME=$(notdir $(shell pwd | sed 's/ /\\/g'))

.PHONY: default send

define remotelaunch
	@echo "  * remote: $(REMOTE)"; \
	echo "  * folder: $(REMOTE_FOLDER)"; \
	echo ""; \
	ssh $(REMOTE) 'make --no-print-directory -C $(REMOTE_FOLDER)/$(APP_NAME) $1 TARGET=local DEPART=true'
endef

default:
ifeq ($(TARGET), local)
ifneq ($(DEPART), true)
	@echo "# locally compiling $(APP_NAME)..."
else
	@echo "# remotely compiling $(APP_NAME)..."
endif
	@make --no-print-dir -f ../common.mk
	@echo ""
else
ifeq ($(TARGET), remote)
	@echo "# remotely compiling $(APP_NAME)..."
	$(call remotelaunch, $@)
endif
endif

clean:
	@make --no-print-dir -f ../common.mk $@





send:
	@make --no-print-dir -C ../ send

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
