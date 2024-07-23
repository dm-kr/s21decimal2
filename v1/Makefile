CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIBS = -lm

HEADERS = s21_decimal.h $(wildcard ./HEADERS/*.c) 


OBJ_LIBRARY := $(patsubst %.c, %.o,  *.c)

%.o: %.c $(HEADER)
	gcc $(CFLAGS) -c $< -o $@

all: s21_decimal.a test gcov_report

main: s21_decimal.c s21_decimal.a
	@gcc $(CFLAGS) m/main.c -o m/main $(LIBS)
	@m/main

s21_decimal.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_decimal.a $(OBJ_LIBRARY)
	ranlib s21_decimal.a
	rm -rf ./*/*.o

test: s21_decimal.a tests/general.c
	gcc $(CFLAGS) tests/general.c s21_decimal.a -o test.out -lm -lcheck -lsubunit 
	./test.out

gcov_report: s21_decimal.a tests/general.c
	gcc $(GCOVFLAGS) tests/general.c $(SOURCES_ALL) -o report.out -lm -lcheck -lsubunit 
	./report.out
	gcov -f $(SOURCES_ALL)
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html

clang:
	clang-format -style=Google -n ./*/*.c

rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov s21_decimal m/main
	rm -rf ./report