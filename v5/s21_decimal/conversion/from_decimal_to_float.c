#include <math.h>

#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./conversion.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int code = 0;
  if (!dst) {
    code = 1;
  } else if (!is_correct(src)) {
    code = 1;
    *dst = 0.0;
  } else if (s21_is_equal(src, Decimal(0))) {
    *dst = get_sign(src) ? -0.0 : 0.0;
  } else {
    double tmp = 0.0;
    for (int i = 0; i < BASE_SIZE; i++) {
      if (get_bit(src, i) != 0) {
        tmp += pow(2.0, i);
      }
    }
    tmp /= pow(10, get_scale(src));
    if (get_sign(src)) tmp *= -1.0;
    *dst = (float)tmp;
  }
  return code;
}
