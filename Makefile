CC=g++
CFLAGS= -c -g -o0 -Wall -std=c++20 -fprofile-arcs -ftest-coverage
LDFLAGS= -lm -lboost_unit_test_framework -lgcov --coverage

SOURCES=tests/list_tests.cpp \
		tests/flist_tests.cpp \
		tests/array_tests.cpp \
		tests/stack_tests.cpp \
		tests/queue_tests.cpp \
		tests/hash_set_tests.cpp \
		tests/hash_table_tests.cpp \
		tests/cbt_tests.cpp

OUTS=$(SOURCES:.cpp=.out)
LOG=gen_html_log.txt

all: $(SOURCES) $(OUTS) genHtml

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ 

.o.out:
	$(CC) $< -o $@ $(LDFLAGS)

run:
	find . -type f -name "*.o" -delete
	clear
	@for out_f in ./tests/*.out; do ./$$out_f; done

LCOV: run
	@echo "lcov start"
	@lcov --capture --directory ./tests --output-file coverage.info > $(LOG)
	@lcov -r coverage.info "/usr*" -o coverage.info > $(LOG)

genHtml: LCOV
	@echo "genhtml start"
	@genhtml coverage.info --output-directory coverage_html > $(LOG)
	@tail -n 3 $(LOG)