# gdb ./clients
# r / run
# bt / backtrace
# f / frame
# print var

CFLAGS ?= -g #debug
# CFLAGS = -O3
override CFLAGS += -Wall -Wpedantic -Wextra -Iinclude

.PHONY: all clean

all: out clients

out: out/db_file out/table out/utils out/ui

clients: src/main.c out/ui/menus.o out/db_file/catalog.o\
			out/db_file/view.o\
		 	out/db_file/db_file_utils.o out/db_file/db_file_admin.o\
			out/table/country.o out/table/job.o out/table/industry.o \
			out/table/group.o out/table/company.o out/table/person.o \
			out/utils/logger.o out/utils/system.o
	gcc $(CFLAGS) -o clients $^

out/%.o: src/%.c include/%.h
	gcc $(CFLAGS) -c -o $@ $<

out/%:
	mkdir -p $@

clean:
	rm -f clients
	rm -rf out
	rm -rf data_clients
	rm -rf data_export
