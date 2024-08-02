#include "./../helpers/helpers.h"
#include "./arithmetic.h"

s21_decimal decimal_abs(s21_decimal value_1) {
  s21_decimal result = value_1;
  set_sign(&result, 0);
  return result;
}
