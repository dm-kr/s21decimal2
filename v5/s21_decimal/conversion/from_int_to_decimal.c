#include <limits.h>

#include "../../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code = 0;
  if (!dst) {
    code = 1;
  } else {
    *dst = Decimal(0);
    set_sign(dst, src >> 31);
    dst->bits[0] = (src < 0 && src != INT_MIN) ? -src : src;
  }
  return code;
}
