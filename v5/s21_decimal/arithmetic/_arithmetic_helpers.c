#include <stdlib.h>

#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./arithmetic.h"

int get_decimal_shift(big_decimal value) {
  int cnt = 0;
  if (!bd_is_null(value)) {
    big_decimal max = tobd(max_decimal());
    big_decimal quotient = bd_bin_div(value, max, NULL);

    while (bin_cmp(quotient.decimals[0], ten_pow(cnt)) > 0) cnt++;
    big_decimal tmp = bd_bin_div(value, tobd(ten_pow(cnt)), NULL);
    if (!is_null(tmp.decimals[1]) || tmp.decimals[0].bits[3] != 0) cnt++;
  }
  return cnt;
}

int s21_max(int value_1, int value_2) {
  return value_1 > value_2 ? value_1 : value_2;
}
