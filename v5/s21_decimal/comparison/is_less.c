#include "./../arithmetic/arithmetic.h"
#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./comparison.h"

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  int code = 0;
  int sign1 = get_sign(value1);
  int sign2 = get_sign(value2);
  if (s21_is_equal(value1, Decimal(0)) && s21_is_equal(value2, Decimal(0))) {
    code = 0;
  } else if (sign1 == 1 && sign2 == 0) {
    code = 1;
  } else if (sign1 == 0 && sign2 == 1) {
    code = 0;
  } else if (sign1 == 1 && sign2 == 1) {
    code = is_less_handle(decimal_abs(value2), decimal_abs(value1));
  } else {
    code = is_less_handle(value1, value2);
  }
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
