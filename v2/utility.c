#include "s21_decimal.h"

int _and(int a, int b) { return a & b; }
int _or(int a, int b) { return a | b; }
int _xor(int a, int b) { return a ^ b; }

s21_decimal logic(s21_decimal value_1, s21_decimal value_2, Operation op) {
  s21_decimal result = Decimal(0);
  for (int i = 0; i < 96; i++) {
    int a = bit(value_1, i);
    int b = bit(value_2, i);
    s_bit(&result, i, op(a, b));
  }
  return result;
}

s21_decimal invert(s21_decimal value) {
  s21_decimal inverted = value;
  for (int i = 0; i < 96; i++) {
    s_bit(&inverted, i, 1 - bit(value, i));
  }
  return inverted;
}

int shift(s21_decimal* value, bool dir, int amount) {
  int carry = 0;
  int temp = 0;
  for (int count = 0; count < amount; count++) {
    carry = 0;
    for (int i = 0; i < 96; i++) {
      int j = !dir ? 95 - i : i;
      temp = bit(*value, j);
      s_bit(value, j, carry);
      carry = temp;
    }
  }
  return carry * dir;
}

bool is_null(s21_decimal value) {
  return value.bits[0] + value.bits[1] + value.bits[2] == 0;
  // TODO переписать
}

s21_decimal to_acode(s21_decimal value) {
  s21_decimal temp = invert(value);
  s_sign(&temp, 0);
  s21_decimal one = Decimal(1);
  s21_add(temp, one, &value);
  return value;
}

int resign(s21_decimal value1, s21_decimal value2) {
  int s = 0;
  int asign = sign(value1);
  int bsign = sign(value2);
  if (asign == bsign) {
    s = asign;
  } else if (is_greater_bm(value1, value2)) {
    s = asign;
  } else {
    s = bsign;
  }
  return s;
}

int is_greater_bm(s21_decimal value1, s21_decimal value2) {
  int result = 0;
  bool got_result = false;
  s21_decimal a = value1;
  s21_decimal b = value2;
  // reduce_power(&a);
  // reduce_power(&b);
  for (int i = 95; i >= 0 && !got_result; i--) {
    if (bit(a, i) != bit(b, i)) {
      if (bit(a, i) > bit(b, i)) {
        result = 1;
      }
      got_result = true;
    }
  }

  return result;
}

int g_zeroes(char* string) {
  int zeroes = 0;
  for (int i = 0; string[i] != 'e'; i++) {
    if (string[i] == '0')
      zeroes++;
    else
      zeroes = 0;
  }
  return zeroes;
}

int get_significants(s21_decimal value) {
  int i = 95;
  for (; i >= 0 && bit(value, i) == 0; i--);
  return i + 1;
}

s21_decimal descale(s21_decimal value) {
  s21_decimal descaled = value;
  int sc = scale(value);
  s21_decimal divider = Decimal(1);
  for (int i = 0; i < sc; i++) {
    s21_mul(divider, Decimal(10), &divider);
  }
  s_scale(&descaled, 0);
  if (sc > 0) s21_div(descaled, divider, &descaled);
  return descaled;
}