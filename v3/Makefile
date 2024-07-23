CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
LDFLAGS = -lcheck -lpthread -lrt -lm -lsubunit 
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lm
BRANCHES = --rc lcov_branch_coverage=1

HEADERS = s21_decimal.h $(wildcard ./HEADERS/*.c) 

OBJ_LIBRARY := $(patsubst %.c, %.o, *.c)

all: s21_decimal.a test gcov_report

main: s21_decimal.c s21_decimal.a
	@gcc $(CFLAGS) m/main.c s21_decimal.a -o m/main $(LIBS)
	@m/main

s21_decimal.a: $(OBJ_LIBRARY) $(HEADERS)
	@gcc $(CFLAGS) -c *.c
	@ar rcs s21_decimal.a *.o
	@ranlib s21_decimal.a
	@rm -rf *.o

test: s21_decimal.a tests/general.c
	${CC}  tests/*.c *.c $(LDFLAGS) --coverage -I. -o test
	./test

test1: s21_decimal.a tests1/s21_decimal_test.c
	${CC}  tests1/*.c *.c $(LDFLAGS) --coverage -I. -o test
	./test

gcov_report: test
	lcov --capture --directory . --output-file test.info $(BRANCHES)
	lcov --remove test.info '*/tests/*' --output-file test.info $(BRANCHES)
	genhtml test.info --output-directory coverage_report $(BRANCHES)
	xdg-open coverage_report/index.html


clang:
	clang-format -style=Google -n ./*/*.c

rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov s21_decimal m/main
	rm -rf coverage_report test.info .clang-format test