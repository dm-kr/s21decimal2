#include "s21_decimal.h"

s21_decimal Decimal(int number) {
  s21_decimal value;
  clear(&value);
  s21_from_int_to_decimal((int)number, &value);
  return value;
}

void clear(s21_decimal* value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}

void print(s21_decimal value) {
  printf("Scale: %d\n", scale(value));
  if (sign(value) == 1) {
    printf(" - ");
  } else {
    printf(" + ");
  }
  for (int i = 95; i >= 0; i--) {
    if (i % 32 == 0 && i > 0) printf(" ");
    printf("%d", bit(value, i));
  }
  printf("\n");
}

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  int error = 1;
  if (dst) {
    clear(dst);
    if (src < 0) {
      s_sign(dst, 1);
      src = abs(src);
    }
    dst->bits[0] = src;
    error = 0;
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  int error = 0;
  s21_decimal tmp = Decimal(0);
  s21_truncate(src, &tmp);
  *dst = tmp.bits[0];
  if (sign(tmp) && *dst != INT_MIN) *dst *= -1;
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  int error = 1;
  int exp = 0;
  int exp_sign = 1;
  clear(dst);
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
      s_sign(dst, 1);
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
    int zeroes = g_zeroes(float_as_str);
    exp = exp * exp_sign + 6 - zeroes;
    if (zeroes) dst->bits[0] /= pow(10, zeroes);
    if (exp < 0) {
      dst->bits[0] *= pow(10, -exp);
      exp = 0;
    }
    s_scale(dst, exp);
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
  int error = 0;

  double tmp = 0.0;

  int s = sign(src);
  int sc = scale(src);

  for (int i = 0; i < 96; i++) {
    tmp += powf(2.0, i) * bit(src, i);
  }

  tmp /= powl(10, sc);
  tmp *= powl(-1, s);

  *dst = (float)tmp;

  return error;
}