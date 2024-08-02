#include <stdlib.h>

#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./../other/other.h"
#include "./arithmetic.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  if (result && is_correct(value_1) && is_correct(value_2)) {
    s21_decimal res = Decimal(0);
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    if (sign1 == 0 && sign2 == 0) {
      code = mul_handle(value_1, value_2, &res);
    } else if (sign1 == 0 && sign2 == 1) {
      code = mul_handle(value_1, decimal_abs(value_2), &res);
      s21_negate(res, &res);
    } else if (sign1 == 1 && sign2 == 0) {
      code = mul_handle(decimal_abs(value_1), value_2, &res);
      s21_negate(res, &res);
    } else if (sign1 == 1 && sign2 == 1) {
      code = mul_handle(decimal_abs(value_1), decimal_abs(value_2), &res);
    }
    if (code == 1 && get_sign(res)) code = 2;
    if (code == 0 && s21_is_not_equal(value_1, Decimal(0)) &&
        s21_is_not_equal(value_2, Decimal(0)) &&
        s21_is_equal(res, Decimal(0))) {
      code = 2;
    }
    *result = res;
  }
  return code;
}

int mul_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  int scale1 = get_scale(value_1);
  int scale2 = get_scale(value_2);
  clear_service(&value_1);
  clear_service(&value_2);
  big_decimal res = bd_bin_mul(tobd(value_1), value_2);
  int shift = get_decimal_shift(res);
  int res_scale = scale1 + scale2 - shift;
  if (res_scale < 0) {
    code = 1;
    *result = inf();
  } else {
    big_decimal remainder = tobd(Decimal(0));
    big_decimal powten = tobd(ten_pow(shift));
    res = bd_bin_div(res, powten, &remainder);
    set_scale(&remainder.decimals[0], shift);
    res.decimals[0] = s21_round_banking(res.decimals[0], remainder.decimals[0]);
    set_scale(&res.decimals[0], res_scale);
    if (!is_null(res.decimals[1]) || !is_correct(res.decimals[0])) {
      code = 1;
      *result = inf();
    } else {
      *result = res.decimals[0];
    }
  }
  return code;
}
