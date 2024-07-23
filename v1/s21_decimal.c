#include "s21_decimal.h"

// Вспомогательные функции

s21_decimal Decimal(int type, float number) {
  s21_decimal value;
  flush_decimal(&value);
  if (type == 0) {
    s21_from_int_to_decimal((int)number, &value);
  } else {
    s21_from_float_to_decimal(number, &value);
  }
  return value;
}

void flush_decimal(s21_decimal* value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

s21_decimal copy_decimal(s21_decimal src) {
  s21_decimal result = Decimal(0, 0);
  for (int i = 0; i < 4; i++) {
    result.bits[i] = src.bits[i];
  }
  return result;
}

void print_decimal(s21_decimal value) {
  for (int i = 95; i >= 0; i--) {
    printf("%d", get_bit(value, i));
  }
  printf("\n");
}

bool get_sign(s21_decimal value) { return (value.bits[3] >> 31); }

void set_sign(s21_decimal* value, int sign) { set_bit(value, 127, sign); }

int get_bit(s21_decimal value, int pos) {
  int res = 0;
  if ((value.bits[pos / 32] & (1 << pos % 32)) != 0) res = 1;
  return res;
}

void set_bit(s21_decimal* value, int pos, int bit) {
  if (bit == 0) {
    value->bits[pos / 32] &= ~(1 << (pos % 32));
  } else {
    value->bits[pos / 32] |= (1 << (pos % 32));
  }
}

int get_power(s21_decimal value) { return (value.bits[3] & 0xFF0000) >> 16; }

void set_power(s21_decimal* value, int power) {
  value->bits[3] = (value->bits[3] & (1 << 31)) | (power << 16);
}

int _and(int a, int b) { return a & b; }
int _or(int a, int b) { return a | b; }
int _xor(int a, int b) { return a ^ b; }

s21_decimal my_boy(s21_decimal value_1, s21_decimal value_2, Operation op) {
  s21_decimal result = Decimal(0, 0);
  for (int i = 0; i < 96; i++) {
    int a = get_bit(value_1, i);
    int b = get_bit(value_2, i);
    set_bit(&result, i, op(a, b));
  }
  return result;
}

void invert(s21_decimal* value) {
  for (int i = 0; i < 96; i++) {
    set_bit(value, i, 1 - get_bit(*value, i));
  }
}

int shift(s21_decimal* value, bool dir, int amount) {
  int carry = 0;
  int temp = 0;
  for (int count = 0; count < amount; count++) {
    carry = 0;
    for (int i = 0; i < 96; i++) {
      int j = !dir ? 95 - i : i;
      temp = get_bit(*value, j);
      set_bit(value, j, carry);
      carry = temp;
    }
  }
  return carry * dir;
}

bool is_null(s21_decimal value) {
  return value.bits[0] + value.bits[1] + value.bits[2] == 0;
}

s21_decimal to_acode(s21_decimal value, int* sign, int* error) {
  *sign = get_sign(value);
  s21_decimal temp = copy_decimal(value);
  // if (get_power(temp)) reduce_power(&temp);
  set_sign(&temp, 0);
  if (*sign) {
    invert(&temp);
    int e = s21_add(temp, Decimal(0, 1), &temp);
    if (error) {
      *error = e;
    }
  }
  return temp;
}

int add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int overflow = 0;
  while (!is_null(value_2)) {
    s21_decimal carry = my_boy(value_1, value_2, _and);
    value_1 = my_boy(value_1, value_2, _xor);
    overflow = shift(&carry, LEFT, 1);
    value_2 = copy_decimal(carry);
  }
  *result = copy_decimal(value_1);
  return overflow;
}

int get_significants(s21_decimal value) {
  int i = 95;
  for (; i >= 0 && get_bit(value, i) == 0; i--);
  return i + 1;
}

void integral_div(s21_decimal val1, s21_decimal val2, s21_decimal* res) {
  s21_decimal a = copy_decimal(val1);
  s21_decimal b = copy_decimal(val2);
  set_power(&a, 0);
  set_power(&b, 0);
  flush_decimal(res);
  int sa = get_significants(a);
  int sb = get_significants(b);
  int asign = get_sign(a);
  int bsign = get_sign(b);
  shift(&b, LEFT, sa - sb);
  while (get_significants(b) >= sb) {
    shift(res, LEFT, 1);
    if (s21_is_greater_or_equal(a, b)) {
      s21_sub(a, b, &a);
      set_bit(res, 0, 1);
    }
    shift(&b, RIGHT, 1);
  }
  set_sign(res, asign ^ bsign);
}

void reduce_power(s21_decimal* value) {
  s21_decimal tmp = *value;
  int sign = get_sign(*value);
  set_sign(&tmp, 0);
  set_power(&tmp, 0);
  s21_decimal divider = Decimal(0, 10);
  int power = get_power(*value);
  for (int i = 0; i < power; i++) {
    // s21_mul(divider, Decimal(0, 10), &divider);
    integral_div(tmp, divider, &tmp);
  }
  set_sign(&tmp, sign);
  *value = copy_decimal(tmp);
}

int find_error(s21_decimal v1, s21_decimal v2, s21_decimal res, int of) {
  int error = 0;
  int as = get_sign(v1);
  int bs = get_sign(v2);
  int rs = get_sign(res);
  if (as + bs == 0 && of) {
    error = 1;
  } else if (as + bs == 2 && rs == 0) {
    error = 2;
  } else if (as + bs == 2) {
    if (s21_is_greater(res, v1) || s21_is_greater(res, v2)) {
      error = 2;
    }
  }
  return error;
}

// 11100100
// 1010

// Основные функции

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int overflow = 0;
  int asign = 0, bsign = 0;
  s21_decimal a = to_acode(value_1, &asign, NULL);
  s21_decimal b = to_acode(value_2, &bsign, NULL);
  // if (get_power(a)) reduce_power(&a);
  // if (get_power(b)) reduce_power(&b);
  flush_decimal(result);
  // printf("\n");
  // print_decimal(a);
  // print_decimal(b);
  while (!is_null(b)) {
    s21_decimal carry = my_boy(a, b, _and);
    a = my_boy(a, b, _xor);
    overflow = shift(&carry, LEFT, 1);
    b = copy_decimal(carry);
  }
  int sign = "01"[(asign + overflow) % 2] - '0';
  set_sign(&a, sign);
  if (sign) {
    set_sign(&a, 0);
    *result = to_acode(a, &sign, NULL);
  } else {
    *result = copy_decimal(a);
  }
  set_sign(result, sign);
  int error = find_error(value_1, value_2, *result, overflow);
  return error;
}

// 0 1 0 1
// 0 0 1 1
// 1 0 1

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  s21_decimal b = copy_decimal(value_2);
  set_sign(&b, !get_sign(b));
  int error = s21_add(value_1, b, result);
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  return get_sign(value_1) || get_sign(value_2) == get_sign(*result);
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  return get_sign(value_1) || get_sign(value_2) == get_sign(*result);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = 0;
  // s21_decimal res = Decimal(0, 0);
  s21_decimal temp = copy_decimal(value_1);
  flush_decimal(result);
  for (int i = 0; i < 96; i++) {
    if (get_bit(value_2, i)) {
      s21_add(*result, temp, result);
    }
    shift(&temp, LEFT, 1);
  }
  set_sign(result, get_sign(value_1) ^ get_sign(value_2));
  return error;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 1;
  bool are_zeros = is_null(value_1) && is_null(value_2);
  for (int i = 0; i < 128 && result == 1; i++) {
    if (get_bit(value_1, i) != get_bit(value_2, i)) result = 0;
  }
  return result || are_zeros;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) || s21_is_greater(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  bool got_result = false;
  s21_decimal a = copy_decimal(value_1);
  s21_decimal b = copy_decimal(value_2);
  reduce_power(&a);
  reduce_power(&b);
  for (int i = 95; i >= 0 && !got_result; i--) {
    if (get_bit(a, i) != get_bit(b, i)) {
      if (get_bit(a, i) > get_bit(b, i)) {
        result = 1;
      }
      got_result = true;
    }
  }
  if ((get_sign(value_1) + get_sign(value_2)) == 2) result = 1 - result;
  if ((get_sign(value_1) > get_sign(value_2)) || s21_is_equal(value_1, value_2))
    result = 0;
  return result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_greater_or_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_equal(value_1, value_2) || s21_is_less(value_1, value_2);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  int error = 1;
  if (dst) {
    flush_decimal(dst);
    if (src < 0) {
      set_sign(dst, 1);
      src = abs(src);
    }
    dst->bits[0] = src;
    error = 0;
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  int error = 0;
  s21_decimal tmp = Decimal(0, 0);
  s21_truncate(src, &tmp);
  *dst = tmp.bits[0];
  if (get_sign(tmp) && *dst != S21_MIN_INT) *dst *= -1;
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  int error = 1;
  int exp = 0;
  int exp_sign = 1;
  flush_decimal(dst);
  if (fabs(src) < powl(10.0, -1 * 28)) {
    error = 1;
  } else if (src >= MAX_DECIMAL) {
    error = 1;
  } else if (src <= MIN_DECIMAL) {
    error = 1;
  } else {
    error = 0;
    bool sign = src < 0;
    if (sign) {
      src = fabsl(src);
      set_sign(dst, 1);
    }
    char float_as_str[16] = {'\0'};
    sprintf(float_as_str, "%.6e", src);
    int i = 0;
    for (; float_as_str[i] != 'e'; i++) {
      if (float_as_str[i] == '.') continue;
      dst->bits[0] *= 10;
      dst->bits[0] += float_as_str[i] - '0';
    }
    i++;
    if (float_as_str[i++] == '+') exp_sign = -1;
    for (; float_as_str[i] != '\0'; i++) {
      exp *= 10;
      exp += float_as_str[i] - '0';
    }
    exp = exp * exp_sign + 6;
    if (exp < 0) {
      dst->bits[0] *= pow(10, -exp);
      exp = 0;
    }
    set_power(dst, exp);
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  int error = 0;

  double tmp = 0.0;

  int sign = get_sign(src);
  int power = get_power(src);

  for (int i = 0; i < 96; i++) {
    tmp += powf(2.0, i) * get_bit(src, i);
  }

  tmp /= powl(10, power);
  tmp *= powl(-1, sign);

  *dst = (float)tmp;

  return error;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  return get_bit(value, 0) == get_bit(*result, 0);
}

int s21_negate(s21_decimal value, s21_decimal* result) {
  int error = 0;
  *result = copy_decimal(value);
  set_sign(result, 1 - get_sign(value));
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  int error = 0;
  *result = Decimal(0, 0);
  s21_decimal tmp = value;
  set_sign(&tmp, 0);
  reduce_power(&tmp);
  set_power(&tmp, 0);
  *result = tmp;
  // s21_decimal divider = Decimal(0, 1);
  // for (int i = 0; i < get_power(value); i++) {
  //   s21_mul(divider, Decimal(0, 10), &divider);
  // }
  // integral_div(tmp, divider, result);
  set_sign(result, get_sign(value));
  return error;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  return get_bit(value, 0) == get_bit(*result, 0);
}
