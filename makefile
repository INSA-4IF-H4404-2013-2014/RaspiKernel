MAKEFLAGS += --no-print-directory
-include .common_parser.mk

APPS=$(dir $(wildcard */makefile))

.PHONY: default clean all send remote all_
.PHONY: $(APPS)

#$1 is the remote rule to launch (default, clean, all...)
define remotelaunch
	@echo "  * remote: $(REMOTE)"; \
	echo "  * folder: $(REMOTE_FOLDER)"; \
	echo ""; \
	ssh $(REMOTE) 'make --no-print-directory -C $(REMOTE_FOLDER) $1 MODE=local DEPART=true'
endef

default: send
ifeq ($(MODE), local)
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
ifeq ($(MODE), remote)
	@echo "# remotely compiling all apps..."
	$(call remotelaunch, $@)
endif
endif

clean:
ifeq ($(MODE), local)
ifneq ($(DEPART), true)
	@echo "# locally cleaning all apps..."
endif
	@echo
	@for APP in $(APPS) ;\
        do\
            make -C "$$APP" clean ;\
        done;
else
ifeq ($(MODE), remote)
	@echo "# remotely cleaning all apps..."
	$(call remotelaunch, $@)
endif
endif

all: send all_

all_:
ifeq ($(MODE), local)
ifneq ($(DEPART), true)
	@echo " # locally cleaning and re-making all apps..."
endif
	@echo
	@for APP in $(APPS) ;\
        do\
            make -C "$$APP" all_ ;\
			echo "" ;\
        done;
else
ifeq ($(MODE), remote)
	@echo " # remotely cleaning and re-making all apps..."
	$(call remotelaunch, all_)
endif
endif

send:
ifeq ($(MODE), remote)
	@echo "# updating remote $(REMOTE):$(REMOTE_FOLDER)..."
ifndef REMOTE_USERNAME
	$(error "Please first set REMOTE_USERNAME variable in $(OPTIONSFILE)!")
else
	@rsync -haP --exclude=.git --exclude=build --exclude=pdfs --delete . $(REMOTE):$(REMOTE_FOLDER)
	@echo
endif
endif
