MAKEFLAGS += --no-print-directory

APPS=$(dir $(wildcard */makefile))

.PHONY: update clean all
.PHONY: $(APPS)

$(APPS):
	@echo "# compiling $@" ;\
	make -C "$@" ;

update: $(APPS)
	@echo "# all builds succeeded" ;

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
