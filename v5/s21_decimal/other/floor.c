#include "./../arithmetic/arithmetic.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./other.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int code = 1;
  if (result && is_correct(value)) {
    code = 0;
    int sign = get_sign(value);
    s21_decimal fractional;
    s21_decimal value_unsigned_truncated;
    s21_decimal value_unsigned = decimal_abs(value);
    s21_truncate(value_unsigned, &value_unsigned_truncated);
    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);
    if (sign == 1 && s21_is_greater(fractional, Decimal(0))) {
      s21_add(value_unsigned_truncated, Decimal(1), &value_unsigned_truncated);
    }
    *result = value_unsigned_truncated;
    set_sign(result, sign);
  }
  return code;
}
