#include <stdio.h>

#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal d1, s21_decimal d2) {
  int code = 1;
  s21_decimal tmp1 = s21_remove_trailing_zeros(d1);
  s21_decimal tmp2 = s21_remove_trailing_zeros(d2);
  if (tmp1.bits[0] == 0 && tmp1.bits[1] == 0 && tmp1.bits[2] == 0 &&
      tmp2.bits[0] == 0 && tmp2.bits[1] == 0 && tmp2.bits[2] == 0) {
    code = 1;
  } else {
    code = tmp1.bits[0] == tmp2.bits[0] && tmp1.bits[1] == tmp2.bits[1] &&
           tmp1.bits[2] == tmp2.bits[2] && tmp1.bits[3] == tmp2.bits[3];
  }

  return code;
}
