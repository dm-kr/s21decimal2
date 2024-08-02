#include "handlers.h"

#include "binary.h"
#include "s21_decimal.h"
#include "utility.h"

int add_handle(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
               int action) {
  int code = 0;
  big_decimal bd1;
  big_decimal bd2;
  big_decimal res;
  int scale1 = get_scale(value_1);
  int scale2 = get_scale(value_2);
  int max_scale = s21_max(scale1, scale2);
  rescaling(value_1, value_2, &bd1, &bd2);
  res = action ? bd_bin_sub(bd1, bd2) : bd_bin_add(bd1, bd2);
  int shift = get_decimal_shift(res);
  int res_scale = max_scale - shift;
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
    if (!is_correct(res.decimals[0])) {
      code = 1;
      *result = inf();
    } else {
      *result = res.decimals[0];
    }
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
    *result = res.decimals[0];
  }
  return code;
}

int div_handle(big_decimal bd2, big_decimal bdres, big_decimal rem,
               s21_decimal *res) {
  int code = 0;
  int scale1 = calc_fractional(&bdres, bd2, &rem);
  big_decimal tmp_res = tobd(Decimal(0));
  int scale2 = calc_fractional(&tmp_res, bd2, &rem);
  set_scale(&tmp_res.decimals[0], scale2);
  bdres.decimals[0] = s21_round_banking(bdres.decimals[0], tmp_res.decimals[0]);
  set_scale(&bdres.decimals[0], scale1);
  *res = bdres.decimals[0];
  return code;
}

int is_less_handle(s21_decimal d1, s21_decimal d2) {
  int code = 0;
  s21_decimal tmp1 = d1;
  s21_decimal tmp2 = d2;
  big_decimal bd1;
  big_decimal bd2;
  rescaling(tmp1, tmp2, &bd1, &bd2);
  int compare = bd_bin_cmp(bd1, bd2);
  if (compare == -1) {
    code = 1;
  } else {
    code = 0;
  }
  return code;
}
