CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lcheck -lpthread -lrt -lm -lsubunit 
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lm
BRANCHES = --rc lcov_branch_coverage=1

OBJ_DIR = obj
TESTS = tests/%
SRCS := $(filter-out tests/%, $(wildcard */*.c))
SRCS := $(filter-out m/main.c, $(SRCS))
HEADERS = $(wildcard ./*/*.h)

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SRCS))

all: s21_decimal.a test gcov_report

main: s21_decimal.a
	@gcc $(CFLAGS) m/main.c s21_decimal.a -o m/main $(LIBS)
	@m/main

s21_decimal.a: $(OBJ_LIBRARY) $(HEADERS)
	@gcc $(CFLAGS) -c $(SRCS)
	@ar rcs s21_decimal.a $(OBJ_LIBRARY)
	@ranlib s21_decimal.a
	@rm -rf $(OBJ_LIBRARY) *.o

test: s21_decimal.a tests/s21_decimal_test.c
	@ ${CC} tests/*.c s21_decimal.a $(LDFLAGS) --coverage -I. -o test
	@./test

gcov_report: test
	@lcov --capture --directory . --output-file test.info $(BRANCHES)
	@lcov --remove test.info '*/tests/*' --output-file test.info $(BRANCHES)
	@genhtml test.info --output-directory coverage_report $(BRANCHES)
	@xdg-open coverage_report/index.html

clang:
	@clang-format -style=Google -n ./*/*.c

valgrind:
	@valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

rebuild: clean all

clean:
	@rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov s21_decimal m/main
	@rm -rf coverage_report test.info .clang-format test