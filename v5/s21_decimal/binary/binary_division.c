#include <stdlib.h>

#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./binary.h"

big_decimal bd_bin_div(big_decimal d1, big_decimal d2, big_decimal *rem) {
  big_decimal remainder = tobd(Decimal(0));
  big_decimal quotient = tobd(Decimal(0));
  if (bd_bin_cmp(d1, d2) == -1) {
    remainder = d1;
  } else if (!bd_is_null(d1)) {
    int signs1_1 = get_significants(d1.decimals[1]);
    int signs1_0 = get_significants(d1.decimals[0]);
    signs1_1 = signs1_1 == -1 ? signs1_0 : MAX_BITS + signs1_1;
    int signs2_1 = get_significants(d2.decimals[1]);
    int signs2_0 = get_significants(d2.decimals[0]);
    signs2_1 = signs2_1 == -1 ? signs2_0 : MAX_BITS + signs2_1;
    int shift = signs1_1 - signs2_1;
    big_decimal divisor = bdshift(d2, LEFT, shift);
    big_decimal dividend = d1;
    int need_sub = 1;
    for (; shift >= 0; shift--) {
      if (need_sub == 1) {
        remainder = bd_bin_sub(dividend, divisor);
      } else {
        remainder = bd_bin_add(dividend, divisor);
      }
      quotient = bdshift(quotient, LEFT, 1);
      if (get_bit(remainder.decimals[1], MAX_BITS - 1) == 0) {
        quotient.decimals[0] = set_bit(quotient.decimals[0], 0);
      }
      need_sub = !get_bit(remainder.decimals[1], MAX_BITS - 1);
      dividend = bdshift(remainder, LEFT, 1);
    }
    if (get_bit(remainder.decimals[1], MAX_BITS - 1)) {
      remainder = bd_bin_add(remainder, divisor);
    }
    remainder = bdshift(remainder, RIGHT, signs1_1 - signs2_1);
  }
  if (rem != NULL) *rem = remainder;
  return quotient;
}
