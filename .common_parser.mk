#makeOptions.gitlocal options parsing
OPTIONSFILE ?= makeOptions.gitlocal
-include $(OPTIONSFILE)
MODE ?= remote
REMOTE_MACHINE ?= iftpserv2.insa-lyon.fr
REMOTE = $(REMOTE_USERNAME)@$(REMOTE_MACHINE)
REMOTE_FOLDER ?= ~/RaspSandbox
SQUEDULER ?= KERNEL_STRATEGY_ROUNDROBIN_ONE
OS ?= OS_RASP

ifeq ($(DEPART), true)
	BUILD_PREFIX = arm-none-eabi-
	GDB_CMD = $(BUILD_PREFIX)gdb
endif
