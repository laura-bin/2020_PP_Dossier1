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

out: out/table out/db_file

clients: src/main.c out/catalog.o out/menus.o out/system.o out/utils.o \
			out/db_file/db_file_utils.o out/db_file/db_file_admin.o\
			out/table/country.o out/table/job.o out/table/industry.o \
			out/table/group.o out/table/company.o out/table/person.o
	gcc $(CFLAGS) -o clients $^

out/%.o: src/%.c include/%.h
	gcc $(CFLAGS) -c -o $@ $<

out/%:
	mkdir -p $@

clean:
	find out -name '*.o' -exec rm {} \+
	rm -f clients data_clients/* data_export/*
	rmdir out/*
	rmdir out
	rmdir data_clients
	rmdir data_export
