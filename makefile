MAKEFLAGS += --no-print-directory
-include .common_parser.mk

APPS=$(dir $(wildcard */makefile))

.PHONY: default clean all send remote
.PHONY: $(APPS)

default:
	@for APP in $(APPS) ;\
        do\
			echo "# compiling $$APP" ;\
            make -C "$$APP" ;\
			echo "" ;\
        done;

clean:
	@for APP in $(APPS) ;\
        do\
            make -C "$$APP" clean ;\
        done;

all:
	@for APP in $(APPS) ;\
        do\
			echo "# compiling $$APP" ;\
            make -C "$$APP" all ;\
			echo "" ;\
        done;

send:
	@make -f common.mk send2
