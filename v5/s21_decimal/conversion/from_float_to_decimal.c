#include <math.h>
#include <stdio.h>

#include "./../helpers/helpers.h"
#include "./conversion.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_conversion_result code = 0;
  if (!dst) {
    code = 1;
  } else if (src == 0.0) {
    *dst = Decimal(0);
  } else if (isinf(src) || isnan(src)) {
    code = 1;
    *dst = inf();
  } else if (fabsf(src) > MAX_FLOAT_TO_CONVERT) {
    code = 1;
    *dst = inf();
  } else if (fabsf(src) < MIN_FLOAT_TO_CONVERT) {
    code = 1;
    *dst = Decimal(0);
  } else {
    *dst = Decimal(0);
    char float_string[64];
    sprintf(float_string, "%.6E", fabsf(src));
    int exp = get_exp(float_string);
    if (exp < -22) sprintf(float_string, "%.*E", exp + 28, fabsf(src));
    *dst = float_string_to_decimal(float_string);
  }
  if (dst && signbit(src) != 0) set_sign(dst, 1);
  return code;
}
