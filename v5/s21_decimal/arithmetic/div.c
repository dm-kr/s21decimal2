#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./../other/other.h"
#include "./arithmetic.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  if (result && s21_is_equal(value_2, Decimal(0))) {
    code = 3;
    *result = inf();
  } else if (result && is_correct(value_1) && is_correct(value_2)) {
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    big_decimal bd1;
    big_decimal bd2;
    rescaling(value_1, value_2, &bd1, &bd2);
    big_decimal rem = tobd(Decimal(0));
    big_decimal res;
    res = bd_bin_div(bd1, bd2, &rem);
    if (res.decimals[0].bits[3] != 0 || !is_null(res.decimals[1])) {
      code = 1 + (sign1 != sign2);
      *result = inf();
    } else {
      code = div_handle(bd2, res, rem, result);
      if (sign1 != sign2) set_sign(result, 1);
      if (get_sign(*result) == 1 && code == 1) code = 2;
      if (code == 0 && s21_is_not_equal(value_1, Decimal(0)) &&
          s21_is_equal(*result, Decimal(0))) {
        code = 2;
      }
    }
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
  if (s21_is_equal(tmp_res.decimals[0], zerofive())) {
    if (!is_null(rem.decimals[0]) || !is_null(rem.decimals[1])) {
      s21_add(tmp_res.decimals[0], min_decimal(), &tmp_res.decimals[0]);
    }
  }
  bdres.decimals[0] = s21_round_banking(bdres.decimals[0], tmp_res.decimals[0]);
  set_scale(&bdres.decimals[0], scale1);
  if (!is_null(bdres.decimals[1]) || !is_correct(bdres.decimals[0])) {
    code = 1;
    *res = inf();
  } else {
    *res = bdres.decimals[0];
  }
  return code;
}

int calc_fractional(big_decimal *res, big_decimal bd2, big_decimal *rem) {
  int scale = 0;
  int flag = 0;
  big_decimal number = *res;
  big_decimal tmp_rem = *rem;
  big_decimal tmp;
  while ((!is_null((*rem).decimals[0]) || !is_null((*rem).decimals[1])) &&
         scale < 28 && !flag) {
    big_decimal number_stored = number;
    big_decimal rem_stored = tmp_rem;
    number = bd_bin_mul(number, Decimal(10));
    tmp_rem = bd_bin_mul(tmp_rem, Decimal(10));
    tmp = bd_bin_div(tmp_rem, bd2, &tmp_rem);
    number = bd_bin_add(number, tmp);
    if (!is_correct(number.decimals[0])) {
      number = number_stored;
      tmp_rem = rem_stored;
      flag = 1;
    } else {
      scale++;
    }
  }
  *res = number;
  *rem = tmp_rem;
  return scale;
}
