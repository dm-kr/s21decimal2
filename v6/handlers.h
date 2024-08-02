#ifndef SRC_HANDLERS_H_
#define SRC_HANDLERS_H_

#include "s21_decimal.h"

int add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
               int action);
int mul_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int div_handle(big_decimal value_2l, big_decimal bdres, big_decimal rem,
               s21_decimal *res);
int is_less_handle(s21_decimal d1, s21_decimal d2);

#endif