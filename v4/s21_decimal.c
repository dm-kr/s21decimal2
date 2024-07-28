#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int ret = 0;
  int overflow = 0;
  int asign = sign(value_1);
  int bsign = sign(value_2);
  int asc = scale(value_1);
  int bsc = scale(value_2);
  bd a = tobd(value_1);
  bd b = tobd(value_2);
  normalize(&a, &b);
  if (!is_null(a) && !is_null(b)) {
    if (asign > bsign) a = to_acode(a);
    if (bsign > asign) b = to_acode(b);
  }
  if (result) {
    clear(result);
    bd tempres = add(a, b);
    if (resign(value_1, value_2) && asign != bsign) tempres = to_acode(tempres);
    tempres.scale = asc > bsc ? asc : bsc;
    overflow = check_overflow(tempres);
    // pbd(tempres);
    // printf("\n\n 96: %d\n\n", get(tempres, 96));
    if (asign && bsign) overflow *= 2;
    *result = tos21(tempres);
    s_sign(result, resign(value_1, value_2));
  }
  if (overflow) ret = overflow;
  if (error(value_1, value_2) || !result) ret = -1;
  return ret;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  return sign(value_1) && sign(value_2) && result;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  return sign(value_1) && sign(value_2) && result;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  return sign(value_1) && sign(value_2) && result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int ret = !s21_is_greater_or_equal(value_1, value_2);
  return error(value_1, value_2) ? -1 : ret;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return error(value_1, value_2) ? -1 : !s21_is_greater(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  bd a = tobd(value_1);
  bd b = tobd(value_2);
  int nulls = is_null(a) && is_null(b);
  int ret = isg(a, b);
  if (sign(value_1) && sign(value_2) && !ise(a, b)) {
    ret = 1 - ret;
  }
  if (sign(value_1) > sign(value_2) && !nulls) ret = 0;
  if (sign(value_2) > sign(value_1) && !nulls) ret = 1;
  return error(value_1, value_2) ? -1 : ret;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int ret = s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
  return error(value_1, value_2) ? -1 : ret;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  bd a = tobd(value_1);
  bd b = tobd(value_2);
  int nulls = is_null(a) && is_null(b);
  int ret = ise(a, b);
  if (sign(value_1) != sign(value_2)) ret = 0;
  if (nulls) ret = 1;
  return error(value_1, value_2) ? -1 : ret;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return error(value_1, value_2) ? -1 : !s21_is_equal(value_1, value_2);
}

// 100.1 | 1 | 10010
// 10.01 | 2 | 1001

int s21_floor(s21_decimal value, s21_decimal* result) {
  return sign(value) && result;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  return sign(value) && result;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  return sign(value) && result;
}

int s21_negate(s21_decimal value, s21_decimal* result) {
  return sign(value) && result;
}
