OPTIONSFILE = ../makeOptions.gitlocal
PARSERFILE = ../.common_parser.mk
include $(PARSERFILE)

OS=$(shell uname -s)

APP_NAME=$(notdir $(shell pwd | sed 's/ /\\/g'))

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
GDB_SCRIPTS = $(call rwildcard,gdb/,*.gdb)

.PHONY: default send clean all all_ sdcopy umount _deploy deploy run $(GDB_SCRIPTS)

define remotelaunch
	@echo "  * remote: $(REMOTE)"; \
	echo "  * folder: $(REMOTE_FOLDER)"; \
	echo ""; \
	ssh $(REMOTE) 'make --no-print-directory -C $(REMOTE_FOLDER)/$(APP_NAME) $1 MODE=local DEPART=true'
endef

default: send
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

all: send all_

all_:
ifeq ($(MODE), local)
ifneq ($(DEPART), true)
	@echo "# locally cleaning and re-making $(APP_NAME)..."
else
	@echo "# remotely cleaning and re-making $(APP_NAME)..."
endif
	@make --no-print-dir -f ../common.mk all
else
ifeq ($(MODE), remote)
	@echo "# remotely cleaning and re-making $(APP_NAME)..."
	@echo "  * remote: $(REMOTE)"; \
	echo "  * folder: $(REMOTE_FOLDER)"; \
	echo ""; \
	ssh $(REMOTE) 'make --no-print-directory -C $(REMOTE_FOLDER)/$(APP_NAME) -f ../common.mk all MODE=local DEPART=true'
endif
endif

send:
ifeq ($(MODE), remote)
	@make --no-print-dir -C ../ send
endif

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
ifeq ($(OS), Darwin)
	@diskutil unmount $(SDCARD)
else
	@umount $(SDCARD)
endif
	@echo

ifeq ($(MODE), local)
deploy_:
	@echo "# locally deploying $(APP_NAME)..."
	@echo

deploy: deploy_ default sdcopy umount
else
ifeq ($(MODE), remote)
deploy_:
	@echo "# remotely deploying $(APP_NAME)..."
	@echo

deploy: deploy_ send default sdcopy umount
endif
endif


ifeq ($(MODE), local)
ifneq ($(DEPART), true)
run:
	@make --no-print-dir -f ../common.mk run

$(GDB_SCRIPTS):
	@make --no-print-dir -f ../common.mk $@
endif
endif
