#include "./binary.h"

int is_null(s21_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0 &&
         value.bits[3] == 0;
}

int bd_is_null(big_decimal bd) {
  return is_null(bd.decimals[0]) && is_null(bd.decimals[1]);
}

int bin_cmp(s21_decimal d1, s21_decimal d2) {
  int result = 0;
  for (int i = MAX_BITS - 1; i >= 0 && result == 0; i--) {
    result = get_bit(d1, i) - get_bit(d2, i);
  }
  return result;
}

int bd_bin_cmp(big_decimal d1, big_decimal d2) {
  int compare = bin_cmp(d1.decimals[1], d2.decimals[1]);
  if (compare == 0) {
    compare = bin_cmp(d1.decimals[0], d2.decimals[0]);
  }
  return compare;
}
