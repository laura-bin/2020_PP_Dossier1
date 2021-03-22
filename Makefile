# gdb ./clients
# r / run
# bt / backtrace
# f / frame
# print var

CFLAGS ?= -g #debug
# CFLAGS = -O3
override CFLAGS += -Wall -Wpedantic -Wextra -Iinclude

objects = out/ui/menus.o out/ui/ui_utils.o \
		out/db_file/admin.o out/db_file/catalog.o out/db_file/open_close.o \
		out/db_file/header.o out/db_file/alpha_index.o out/db_file/num_index.o \
		out/search/search_result.o out/search/binary_search.o out/search/sequential_search.o \
		out/search/num_index_search.o out/search/alpha_index_search.o \
		out/display_search/display_binary_search.o out/display_search/display_sequential_search.o \
		out/display_search/display_num_index_search.o out/display_search/display_alpha_index_search.o \
		out/report/report_file.o out/report/people_by_group.o out/report/companies_by_group.o \
		out/report/people_count_by_group.o out/report/people_shares_sum.o \
		out/table/country.o out/table/job.o out/table/industry.o \
		out/table/group.o out/table/company.o out/table/person.o \
		out/utils/logger.o out/utils/system.o out/utils/linked_list.o \
		out/utils/string_utils.o out/utils/sort.o

integration_tests = out/tests/integrations/main_test_create_db

unit_tests = out/tests/units/string_utils out/tests/units/sort

directories = out/db_file out/table out/search out/utils out/ui out/display_search out/report out/tests/units out/tests/integrations

.PRECIOUS: $(integration_tests) $(unit_tests)
.PHONY: all clean tests 

all: out clients

tests: run_integration_tests run_unit_tests

run_integration_tests: $(patsubst out/tests/%,run_test/%, $(integration_tests))

run_unit_tests: $(patsubst out/tests/%,run_test/%, $(unit_tests))

run_test/%: out/tests/%
	@echo -e "\n\n> Running ./$<\n"
	@-./$^

out/tests/%: tests/%.c $(objects)
	gcc $(CFLAGS) -o $@ $^

clients: src/main.c $(objects)
	gcc $(CFLAGS) -o $@ $^

out/%.o: src/%.c include/%.h
	gcc $(CFLAGS) -c -o $@ $<

out: $(directories)
	mkdir -p $@

out/%:
	mkdir -p $@

clean:
	rm -f clients
	rm -rf out
	rm -rf data_clients
	rm -rf data_export
	rm -rf data_report
