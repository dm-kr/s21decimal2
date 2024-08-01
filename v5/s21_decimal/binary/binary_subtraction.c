#include "./../helpers/helpers.h"
#include "./binary.h"

s21_decimal bin_sub(s21_decimal d1, s21_decimal d2) {
  s21_decimal result;
  d2 = invert(d2);
  d2 = bin_add(d2, Decimal(1));
  result = bin_add(d1, d2);
  return result;
}

big_decimal bd_bin_sub(big_decimal d1, big_decimal d2) {
  big_decimal result;
  d2.decimals[0] = invert(d2.decimals[0]);
  d2.decimals[1] = invert(d2.decimals[1]);
  big_decimal one = tobd(Decimal(1));
  d2 = bd_bin_add(d2, one);
  result = bd_bin_add(d1, d2);
  return result;
}
