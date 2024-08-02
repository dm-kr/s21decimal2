#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./arithmetic.h"

void rescaling(s21_decimal d1, s21_decimal d2, big_decimal *bd1,
               big_decimal *bd2) {
  int scale1 = get_scale(d1);
  int scale2 = get_scale(d2);
  s21_decimal tmp1 = d1;
  s21_decimal tmp2 = d2;
  clear_service(&tmp1);
  clear_service(&tmp2);
  *bd1 = tobd(tmp1);
  *bd2 = tobd(tmp2);
  if (scale1 > scale2) {
    *bd2 = bd_bin_mul(tobd(tmp2), ten_pow(scale1 - scale2));
  } else if (scale1 < scale2) {
    *bd1 = bd_bin_mul(tobd(tmp1), ten_pow(scale2 - scale1));
  }
}
