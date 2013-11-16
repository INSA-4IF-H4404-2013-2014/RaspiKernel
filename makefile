MAKEFLAGS += --no-print-directory

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
            make -C "$$APP" all ;\
        done;

send:
	@make -f common.mk send2

remote:
	@for APP in $(APPS) ;\
        do\
			echo "# compiling $$APP" ;\
            make -C "$$APP" remote ;\
        done;
