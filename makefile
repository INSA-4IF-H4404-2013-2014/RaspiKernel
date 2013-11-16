MAKEFLAGS += --no-print-directory
-include .common_parser.mk

APPS=$(dir $(wildcard */makefile))

.PHONY: default clean all send remote
.PHONY: $(APPS)

default:
ifeq ($(TARGET), local)
ifneq ($(DEPART), true)
	@echo "# locally compiling all apps..."
endif
	@echo
	@for APP in $(APPS) ;\
        do\
			echo "# compiling $$APP" ;\
            make -C "$$APP" ;\
			echo "" ;\
        done;
else
ifeq ($(TARGET), remote)
	@echo "# remotely compiling all apps..."
	@echo "  * remote: $(REMOTE)"
	@echo "  * folder: $(REMOTE_FOLDER)"
	@echo
	@ssh $(REMOTE) 'make $(MAKEFLAGS) -C $(REMOTE_FOLDER) default TARGET=local DEPART=true'
endif
endif

clean:
ifeq ($(TARGET), local)
ifneq ($(DEPART), true)
	@echo "# locally cleaning all apps..."
endif
	@echo
	@for APP in $(APPS) ;\
        do\
			echo "# cleaning $$APP" ;\
            make -C "$$APP" clean ;\
        done;
else
ifeq ($(TARGET), remote)
	@echo "# remotely cleaning all apps..."
	@echo "  * remote: $(REMOTE)"
	@echo "  * folder: $(REMOTE_FOLDER)"
	@ssh $(REMOTE) 'make $(MAKEFLAGS) -C $(REMOTE_FOLDER) clean TARGET=local DEPART=true'
endif
endif

all:
ifeq ($(TARGET), local)
ifneq ($(DEPART), true)
	@echo " # locally cleaning and re-making all apps..."
endif
	@echo
	@for APP in $(APPS) ;\
        do\
			echo "# re-making $$APP" ;\
            make -C "$$APP" all ;\
			echo "" ;\
        done;
else
ifeq ($(TARGET), remote)
	@echo "# remotely cleaning and re-making all apps..."
	@echo "  * remote: $(REMOTE)"
	@echo "  * folder: $(REMOTE_FOLDER)"
	@ssh $(REMOTE) 'make $(MAKEFLAGS) -C $(REMOTE_FOLDER) all TARGET=local DEPART=true'
endif
endif

send:
	@make -f common.mk send2
