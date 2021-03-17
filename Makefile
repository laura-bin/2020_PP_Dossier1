# gdb ./clients
# r / run
# bt / backtrace
# f / frame
# print var

CFLAGS ?= -g #debug
# CFLAGS = -O3
override CFLAGS += -Wall -Wpedantic -Wextra -Iinclude

.PHONY: all clean tests

all: out clients

tests: out tests/test_sort
	./tests/test_sort

tests/test_sort: tests/test_sort.c out/utils/sort.o
	gcc $(CFLAGS) -o $@ $<
	# gcc $(CFLAGS) -o $@ $^

out: out/db_file out/table out/search out/utils out/ui out/display_search out/report

clients: src/main.c out/ui/menus.o out/ui/ui-utils.o \
			out/db_file/admin.o out/db_file/catalog.o out/db_file/open_close.o \
			out/db_file/header.o out/db_file/alpha_index.o out/db_file/num_index.o \
			out/search/search_result.o out/search/binary_search.o out/search/sequential_search.o \
			out/search/num_index_search.o out/search/alpha_index_search.o \
			out/display_search/display_binary_search.o out/display_search/display_sequential_search.o \
			out/display_search/display_num_index_search.o out/display_search/display_alpha_index_search.o \
			out/report/report_file.o out/report/people_by_group.o out/report/companies_by_group.o \
			out/report/people_count_by_groups.o out/report/people_shares_sum.o \
			out/table/country.o out/table/job.o out/table/industry.o \
			out/table/group.o out/table/company.o out/table/person.o \
			out/utils/logger.o out/utils/system.o out/utils/linked_list.o \
			out/utils/string_comparison.o out/utils/sort.o
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
	rm -rf data_report
	rm -f tests/test_sort
