OPTIONSFILE = ../makeOptions.gitlocal
PARSERFILE = ../.common_parser.mk
include $(PARSERFILE)

APP_NAME=$(notdir $(shell pwd | sed 's/ /\\/g'))

.PHONY: default send

define remotelaunch
	@echo "  * remote: $(REMOTE)"; \
	echo "  * folder: $(REMOTE_FOLDER)"; \
	echo ""; \
	ssh $(REMOTE) 'make --no-print-directory -C $(REMOTE_FOLDER)/$(APP_NAME) $1 MODE=local DEPART=true'
endef

default:
ifeq ($(MODE), local)
ifneq ($(DEPART), true)
	@echo "# locally compiling $(APP_NAME)..."
else
	@echo "# remotely compiling $(APP_NAME)..."
endif
	@make --no-print-dir -f ../common.mk
	@echo ""
else
ifeq ($(MODE), remote)
	@echo "# remotely compiling $(APP_NAME)..."
	$(call remotelaunch, $@)
endif
endif

clean:
ifeq ($(MODE), local)
ifneq ($(DEPART), true)
	@echo "# locally cleaning $(APP_NAME)..."
else
	@echo "# remotely cleaning $(APP_NAME)..."
endif
	@make --no-print-dir -f ../common.mk $@
else
ifeq ($(MODE), remote)
	@echo "# remotely cleaning $(APP_NAME)..."
	$(call remotelaunch, $@)
endif
endif

all:
ifeq ($(MODE), local)
ifneq ($(DEPART), true)
	@echo "# locally cleaning and re-making $(APP_NAME)..."
else
	@echo "# remotely cleaning and re-making $(APP_NAME)..."
endif
	@make --no-print-dir -f ../common.mk $@
else
ifeq ($(MODE), remote)
	@echo "# remotely cleaning and re-making $(APP_NAME)..."
	$(call remotelaunch, $@)
endif
endif

send:
	@make --no-print-dir -C ../ send

sdcopy:
ifeq ($(MODE), local)
	@echo "# locally deploying kernel.img on SDCARD..."
	@cp build/kernel.img $(SDCARD)
else
ifeq ($(MODE), remote)
	@echo "# remote deploying kernel.img on SDCARD..."
	@scp $(REMOTE):$(REMOTE_FOLDER)/$(APP_NAME)/build/kernel.img $(SDCARD)
	@echo
endif
endif

umount:
	@echo "# unmounting SDCARD..."
	@umount $(SDCARD)
	@echo

deploy: send remote sdcopy umount
