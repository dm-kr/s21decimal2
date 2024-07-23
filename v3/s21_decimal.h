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

#define RIGHT 0
#define LEFT 1

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

typedef struct bd {
  unsigned int bits[9];
} bd;

// 1111111111111111 1111111111111111 1111111111111111 | 1 1111111 11111111

typedef int (*Operation)(int, int);

// Вспомогательные функции

s21_decimal Decimal(int number);
void clear(s21_decimal* value);
void print(s21_decimal value);
int sign(s21_decimal value);
int bit(s21_decimal value, int pos);
int scale(s21_decimal value);
void s_sign(s21_decimal* value, unsigned int sign);
void s_bit(s21_decimal* value, int pos, int bit);
void s_scale(s21_decimal* value, int scale);
int bsign(bd value);
int bbit(bd value, int pos);
int bscale(bd value);
void bs_sign(bd* value, unsigned int sign);
void bs_bit(bd* value, int pos, int bit);
void bs_scale(bd* value, int scale);
s21_decimal invert(s21_decimal value);
s21_decimal logic(s21_decimal value_1, s21_decimal value_2, Operation op);
int _and(int a, int b);
int _or(int a, int b);
int _xor(int a, int b);
int shift(s21_decimal* value, bool dir, int amount);
bool is_null(s21_decimal value);
s21_decimal to_acode(s21_decimal value);
int resign(s21_decimal value1, s21_decimal value2);
int is_greater_bm(s21_decimal value1, s21_decimal value2);
int g_zeroes(char* string);
int get_significants(s21_decimal value);
s21_decimal descale(s21_decimal value);
bd tobd(s21_decimal value);
int tos21(bd value, s21_decimal* res);
int is_decimal(bd value);
int is_correct(s21_decimal value);

// Основные функции

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);  //
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);
int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);

#endif