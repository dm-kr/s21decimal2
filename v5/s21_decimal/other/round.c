#include "./../arithmetic/arithmetic.h"
#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./other.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int code = 1;
  if (result && is_correct(value)) {
    code = 0;
    int sign = get_sign(value);
    s21_decimal fractional;
    s21_decimal value_unsigned_truncated;
    s21_decimal value_unsigned = decimal_abs(value);
    s21_truncate(value_unsigned, &value_unsigned_truncated);
    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);
    s21_decimal half = zerofive();
    if (s21_is_greater_or_equal(fractional, half)) {
      *result = bin_add(value_unsigned_truncated, Decimal(1));
    } else {
      *result = value_unsigned_truncated;
    }
    set_sign(result, sign);
  }
  return code;
}
