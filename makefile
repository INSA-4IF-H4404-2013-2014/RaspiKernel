MAKEFLAGS += --no-print-directory
-include .common_parser.mk

APPS=$(dir $(wildcard */makefile))

.PHONY: default clean all send remote
.PHONY: $(APPS)

#$1 is the remote rule to launch (default, clean, all...)
define remotelaunch
	@echo "  * remote: $(REMOTE)"; \
	echo "  * folder: $(REMOTE_FOLDER)"; \
	echo ""; \
	ssh $(REMOTE) 'make --no-print-directory -C $(REMOTE_FOLDER) $1 TARGET=local DEPART=true'
endef

default:
ifeq ($(TARGET), local)
ifneq ($(DEPART), true)
	@echo "# locally compiling all apps..."
endif
	@echo
	@for APP in $(APPS) ;\
        do\
            make -C "$$APP" ;\
			echo "" ;\
        done;
else
ifeq ($(TARGET), remote)
	@echo "# remotely compiling all apps..."
	$(call remotelaunch, $@)
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
            make -C "$$APP" clean ;\
        done;
else
ifeq ($(TARGET), remote)
	@echo "# remotely cleaning all apps..."
	$(call remotelaunch, $@)
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
	@echo " # remotely cleaning and re-making all apps..."
	$(call remotelaunch, $@)
endif
endif

send:
	@echo "# updating remote $(REMOTE):$(REMOTE_FOLDER)..."
ifndef REMOTE_USERNAME
	$(error "Please first set REMOTE_USERNAME variable in $(OPTIONSFILE)!")
else
	@rsync -haP --exclude=.git --exclude=build --exclude=pdfs --delete . $(REMOTE):$(REMOTE_FOLDER)
	@echo
endif
