# gdb ./main
# r / run
# bt / backtrace
# f / frame
# print var

CFLAGS = -g #debug
# CFLAGS = -O3
 CFLAGS += -Wall -Wpedantic -Wextra

.PHONY: all clean

all: main

main: DB_Main.c DB_Main.h DB_File.o DB_Country.o DB_Job.o DB_Industry.o DB_Group.o
	gcc $(CFLAGS) -o main $^

%.o: %.c DB_Main.h
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o main Data_Export/* Data_DB_Comp/*