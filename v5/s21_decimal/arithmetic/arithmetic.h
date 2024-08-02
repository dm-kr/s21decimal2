#ifndef SRC_S21_DECIMAL_ARITHMETIC_ARITHMETIC_H_
#define SRC_S21_DECIMAL_ARITHMETIC_ARITHMETIC_H_

#include "./../types.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
               int action);
int mul_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int div_handle(big_decimal value_2l, big_decimal bdres, big_decimal rem,
               s21_decimal *res);
int calc_fractional(big_decimal *res, big_decimal value_2l, big_decimal *rem);

void rescaling(s21_decimal d1, s21_decimal d2, big_decimal *bd1,
               big_decimal *bd2);
s21_decimal decimal_abs(s21_decimal value_1);

int get_decimal_shift(big_decimal value);
int s21_max(int value_1, int value_2);

#endif  //  SRC_S21_DECIMAL_ARITHMETIC_ARITHMETIC_H_
