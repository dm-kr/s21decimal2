#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = 0;
  int overflow = 0;
  int save = 0;
  unsigned int asign = sign(value_1);
  unsigned int bsign = sign(value_2);
  s21_decimal a = value_1;
  s21_decimal b = value_2;
  a = descale(a);
  b = descale(b);
  if (!is_null(a) && !is_null(b)) {
    if (asign > bsign) a = to_acode(a);
    if (bsign > asign) b = to_acode(b);
  }
  clear(result);
  s21_decimal carry = Decimal(0);
  while (!is_null(b)) {
    carry = logic(a, b, _and);
    a = logic(a, b, _xor);
    save = overflow;
    overflow = shift(&carry, LEFT, 1);
    b = carry;
  }
  if (!(asign | bsign)) {
    error |= (save | overflow);
  } else if (asign && bsign) {
    error = error != 0 ? error : 2 * (save | overflow);
  }
  if ((asign != bsign) && resign(value_1, value_2)) {
    a = to_acode(a);
  }
  *result = a;
  s_sign(result, resign(value_1, value_2));
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  s21_decimal b = value_2;
  s_sign(&b, !sign(b));
  int error = s21_add(value_1, b, result);
  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = 0;
  int serror = 0;
  // s21_decimal res = Decimal(0, 0);
  s21_decimal a = descale(value_1);
  s21_decimal b = descale(value_2);
  clear(result);
  for (int i = 0; i < 96 && error == 0 && serror != 2; i++) {
    if (bit(b, i)) {
      error = s21_add(*result, a, result);
      if (serror == 1) error = 1;
    }
    serror |= shift(&a, LEFT, 1);
  }
  s_sign(result, sign(value_1) ^ sign(value_2));
  s_scale(result, scale(value_1) + scale(value_2));
  if (sign(value_1) ^ sign(value_2)) error *= 2;
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = 0;
  if (is_null(value_2)) error = 3;
  s21_decimal a = value_1;
  s21_decimal b = value_2;
  clear(result);
  int sa = get_significants(a);
  int sb = get_significants(b);
  int asign = sign(a);
  int bsign = sign(b);
  shift(&b, LEFT, sa - sb);
  while (get_significants(b) >= sb && error == 0) {
    shift(result, LEFT, 1);
    if (s21_is_greater_or_equal(a, b)) {
      s21_sub(a, b, &a);
      s_bit(result, 0, 1);
    }
    shift(&b, RIGHT, 1);
  }
  s_sign(result, asign ^ bsign);
  return error;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_greater_or_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) || s21_is_less(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal a = descale(value_1);
  s21_decimal b = descale(value_2);
  int result = is_greater_bm(a, b);
  // if (result == 0 && scale(value_1) < scale(value_2)) result = 1;
  // if (result == 1 && scale(value_2) < scale(value_1)) result = 0;
  if ((sign(value_1) + sign(value_2)) == 2) result = 1 - result;
  if ((sign(value_1) > sign(value_2)) || s21_is_equal(a, b)) result = 0;
  return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) || s21_is_greater(value_1, value_2);
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  bool are_zeros = is_null(value_1) && is_null(value_2);

  // TODO Отбросить нули

  for (int i = 0; i < 128 && result == 1; i++) {
    if (bit(value_1, i) != bit(value_2, i)) result = 0;
  }
  return result || are_zeros;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  int error = 0;
  s21_decimal temp = descale(value);
  if (scale(value) && sign(value)) {
    error = s21_add(temp, Decimal(-1), &temp);
  }
  *result = temp;
  return error;
}
// 123.456
// 123
// 000.456
// 000.500
int s21_round(s21_decimal value, s21_decimal* result) {
  int error = 0;
  s21_decimal temp = descale(value);
  s21_decimal temp_scaled = temp;
  s21_decimal remainder = Decimal(0);
  s21_decimal check = Decimal(1);
  for (int i = 0; i < scale(value); i++) {
    s21_mul(check, Decimal(10), &check);
    s21_mul(temp_scaled, Decimal(10), &temp_scaled);
  }
  shift(&check, RIGHT, 1);
  s21_sub(value, temp_scaled, &remainder);
  if (scale(value) && sign(value)) {
    error = s21_add(temp, Decimal(-1), &temp);
  }
  if (s21_is_greater_or_equal(remainder, check)) {
    s21_add(temp, Decimal(1), &temp);
  }
  *result = temp;
  return error;
}

int s21_negate(s21_decimal value, s21_decimal* result) {
  int error = 0;
  *result = value;
  s_sign(result, 1 - sign(value));
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  int error = 0;
  if (!result) {
    error = 1;
  } else if (!is_correct(value)) {
    error = 1;
    s21_decimal inf = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
    *result = inf;
  } else {
    clear(result);
    s21_decimal tmp = value;
    s_sign(&tmp, 0);
    tmp = descale(tmp);
    *result = tmp;
    s_sign(result, sign(value));
  }
  return error;
}
