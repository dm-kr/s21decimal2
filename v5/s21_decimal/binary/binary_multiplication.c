#include "./../helpers/helpers.h"
#include "./binary.h"

big_decimal bd_bin_mul(big_decimal d1, s21_decimal d2) {
  big_decimal res = tobd(Decimal(0));
  big_decimal tmp = d1;
  int significants = get_significants(d2);
  for (int i = 0; i <= significants; i++) {
    if (get_bit(d2, i) != 0) {
      res = bd_bin_add(res, tmp);
    }
    tmp = bdshift(tmp, LEFT, 1);
  }
  return res;
}
