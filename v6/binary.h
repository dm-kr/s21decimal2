#ifndef SRC_BINARY_H_
#define SRC_BINARY_H_

#include "s21_decimal.h"

#define RIGHT 0
#define LEFT 1

typedef int (*Op)(int, int);

s21_decimal bshift(s21_decimal value, int dir, int amount);
big_decimal bdshift(big_decimal value, int dir, int amount);

int get_bit(s21_decimal value, int index);
s21_decimal set_bit(s21_decimal value, int index);
int get_significants(s21_decimal value);

int is_null(s21_decimal value);
int bd_is_null(big_decimal bd);
int bin_cmp(s21_decimal d1, s21_decimal d2);
int bd_bin_cmp(big_decimal d1, big_decimal d2);

int _and(int a, int b);
int _xor(int a, int b);

s21_decimal decimal_logic(s21_decimal d1, s21_decimal d2, Op op);
s21_decimal invert(s21_decimal value);

s21_decimal bin_add(s21_decimal d1, s21_decimal d2);
s21_decimal bin_sub(s21_decimal d1, s21_decimal d2);
big_decimal bd_bin_add(big_decimal d1, big_decimal d2);
big_decimal bd_bin_sub(big_decimal d1, big_decimal d2);
big_decimal bd_bin_div(big_decimal d1, big_decimal d2, big_decimal *rem);
big_decimal bd_bin_mul(big_decimal d1, s21_decimal d2);

#endif