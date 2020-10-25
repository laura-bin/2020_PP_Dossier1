# gdb ./main
# r / run
# bt / backtrace
# f / frame
# print var

CFLAGS = -g #debug
# CFLAGS = -O3

.PHONY: all

all: main

main: DB_Main.c DB_Main.h DB_File.o DB_Country.o
	gcc $(CFLAGS) -o main $^

%.o: %.c DB_Main.h
	gcc $(CFLAGS) -c -o $@ $<