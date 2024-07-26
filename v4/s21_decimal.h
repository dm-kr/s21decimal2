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

#define BDSIZE 8
#define BDBITS BDSIZE * 32

typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

typedef struct bd {
  int bits[BDSIZE];
  int sign;
  int scale;
  int overflow;
} bd;

typedef int (*Operation)(int, int);

// Вспомогательные функции

s21_decimal Decimal(int number);
int sign(s21_decimal value);
int bit(s21_decimal value, int pos);
int scale(s21_decimal value);
void s_sign(s21_decimal* value, unsigned int sign);
void s_bit(s21_decimal* value, int pos, int bit);
void s_scale(s21_decimal* value, int scale);
void clear(s21_decimal* value);
void print(s21_decimal value);
bd tobd(s21_decimal value);
s21_decimal tos21(bd value);
void pbd(bd value);
int get(bd value, int bit);
void set(bd* value, int bit, int val);
int _and(int a, int b);
int _or(int a, int b);
int _xor(int a, int b);
bd logic(bd value_1, bd value_2, Operation op);
bd shift(bd value, int dir, int n);
int is_null(bd value);
bd add(bd v1, bd v2);
bd invert(bd value);
bd to_acode(bd value);
bd sub(bd v1, bd v2);
void normalize(bd* v1, bd* v2);
int isg(bd v1, bd v2);
int ise(bd v1, bd v2);
int isgore(bd v1, bd v2);
bd upscale(bd value, int n);
int get_significants(bd value);
bd _div(bd v1, bd v2);
bd downscale(bd value, int n);
int is_correct(s21_decimal val);
int error(s21_decimal v1, s21_decimal v2);
int resign(s21_decimal value1, s21_decimal value2);
int check_overflow(bd value);

// Основные функции

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);  //
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
int s21_floor(s21_decimal value, s21_decimal* result);     //
int s21_round(s21_decimal value, s21_decimal* result);     //
int s21_truncate(s21_decimal value, s21_decimal* result);  //
int s21_negate(s21_decimal value, s21_decimal* result);

#endif