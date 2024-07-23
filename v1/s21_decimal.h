#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DECIMAL powl(2.0, 96)
#define MIN_DECIMAL -1 * MAX_DECIMAL

#define S21_MAX_UINT 4294967295

#define S21_MAX_INT 2147483647
#define S21_MIN_INT -2147483648

#define RIGHT 0
#define LEFT 1

typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

typedef int (*Operation)(int, int);

// Вспомогательные функции

s21_decimal Decimal(int type, float number);
void flush_decimal(s21_decimal* value);
s21_decimal copy_decimal(s21_decimal src);
void print_decimal(s21_decimal value);
bool get_sign(s21_decimal value);
void set_sign(s21_decimal* value, int sign);
int get_bit(s21_decimal value, int pos);
void set_bit(s21_decimal* value, int pos, int bit);
int get_power(s21_decimal value);
void set_power(s21_decimal* value, int power);
int _and(int a, int b);
int _or(int a, int b);
int _xor(int a, int b);
s21_decimal my_boy(s21_decimal value_1, s21_decimal value_2, Operation op);
void invert(s21_decimal* value);
int shift(s21_decimal* value, bool dir, int amount);
bool is_null(s21_decimal value);
s21_decimal to_acode(s21_decimal value, int* sign, int* error);
int add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int get_significants(s21_decimal value);
void integral_div(s21_decimal val1, s21_decimal val2, s21_decimal* res);
void reduce_power(s21_decimal* value);
int find_error(s21_decimal v1, s21_decimal v2, s21_decimal res, int of);

// Основные функции

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);
int s21_floor(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
s21_decimal* s21_copy(s21_decimal* dest, s21_decimal src);
s21_decimal* s21_reset(s21_decimal* value);

#endif