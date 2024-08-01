#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./other.h"

s21_decimal s21_remove_trailing_zeros(s21_decimal value) {
  s21_decimal result = value;
  int scale = get_scale(value);
  int sign = get_sign(value);
  if (scale > 0 && is_correct(value)) {
    big_decimal remainder = tobd(Decimal(0));
    big_decimal tmp = tobd(value);
    clear_service(&tmp.decimals[0]);
    clear_service(&tmp.decimals[1]);
    while (scale > 0 && bd_is_null(remainder)) {
      tmp = bd_bin_div(tmp, tobd(ten_pow(1)), &remainder);
      if (bd_is_null(remainder)) {
        scale--;
        result = tmp.decimals[0];
      }
    }
    set_scale(&result, scale);
    set_sign(&result, sign);
  }

  return result;
}