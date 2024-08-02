CC = gcc
COVDIR = test_info
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lcheck -lpthread -lrt -lm -lsubunit --coverage
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lm
BRANCHES = --rc lcov_branch_coverage=1
SUPPRESS = >> /dev/null 2>&1

SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SRCS))

all: clean s21_decimal.a test gcov_report

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

main: s21_decimal.a
	@$(CC) $(CFLAGS) m/main.c s21_decimal.a -o m/main $(LIBS)
	@m/main

s21_decimal.a: clean $(OBJ_LIBRARY) $(HEADERS)
	@$(CC) $(CFLAGS) -c $(SRCS)
	@ar rcs s21_decimal.a $(OBJ_LIBRARY)
	@ranlib s21_decimal.a
	@rm -rf $(OBJ_LIBRARY) *.o

test: s21_decimal.a tests/s21_decimal_test.c
	@mkdir -p $(COVDIR)
	@${CC} tests/*.c *.c $(LDFLAGS) -I. -o $(COVDIR)/test $(SUPPRESS)
	@$(COVDIR)/test

gcov_report: test
	@lcov --capture --directory $(COVDIR) --output-file $(COVDIR)/test.info $(BRANCHES) $(SUPPRESS)
	@lcov --remove $(COVDIR)/test.info '/usr/include/*' '*/tests/*' --output-file $(COVDIR)/test.info $(BRANCHES) $(SUPPRESS)
	@genhtml $(COVDIR)/test.info --output-directory coverage_report $(BRANCHES) >> $(COVDIR)/genhtml.log 2>&1
	@bash tests/coverage.sh $(COVDIR)
	@xdg-open coverage_report/index.html $(SUPPRESS)

clang:
	@clang-format -style=Google -n ./*/*.c

valgrind:
	@valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

cppcheck:
	@cppcheck --enable=all *.c *.h --suppress=unusedFunction --suppress=missingIncludeSystem

clean:
	@rm -f *.o *.a $(COVDIR)/*.gcno $(COVDIR)/*.gcda $(COVDIR)/*.info *.out *.gcov s21_decimal.a m/main
	@rm -rf coverage_report $(COVDIR) .clang-format test $(COVDIR)/test

.PHONY: run-test run-gcov test gcov_report s21_decimal.a all clean
