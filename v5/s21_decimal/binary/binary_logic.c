#include "./../helpers/helpers.h"
#include "./binary.h"

int _and(int a, int b) { return a & b; }
int _xor(int a, int b) { return a ^ b; }

s21_decimal decimal_logic(s21_decimal d1, s21_decimal d2, Op op) {
  s21_decimal result = Decimal(0);
  for (int i = 0; i < 4; i++) {
    result.bits[i] = op(d1.bits[i], d2.bits[i]);
  }
  return result;
}

s21_decimal invert(s21_decimal value) {
  s21_decimal result = Decimal(0);
  for (int i = 0; i < 4; i++) {
    result.bits[i] = ~value.bits[i];
  }
  return result;
}
