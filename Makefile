# gdb ./clients
# r / run
# bt / backtrace
# f / frame
# print var

CFLAGS = -g #debug
# CFLAGS = -O3
 CFLAGS += -Wall -Wpedantic -Wextra -Iinc

.PHONY: all clean

all: clients

clients: src/main.c out/catalog.o out/db_file.o out/menus.o out/system.o out/utils.o
	gcc $(CFLAGS) -o clients $^

out/%.o: src/%.c inc/%.h
	gcc $(CFLAGS) -c -o $@ $<

clean:
	find out -name '*.o' -exec rm {} \+
	rm -f clients datas/* Data_Export/* Data_DB_Comp/*
	rmdir datas