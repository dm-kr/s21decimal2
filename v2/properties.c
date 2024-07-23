#include "s21_decimal.h"

int sign(s21_decimal value) { return (value.bits[3] >> 31) != 0; }

int bit(s21_decimal value, int pos) {
  return ((value.bits[pos / 32] & (1 << pos % 32)) != 0);
}
// 1111111111111111 1111111111111111 1111111111111111 | 1 1111111 11111111
int scale(s21_decimal value) { return (value.bits[3] & 0xFF0000) >> 16; }

void s_sign(s21_decimal* value, unsigned int sign) {
  s_bit(value, 127, sign != 0);
}

void s_bit(s21_decimal* value, int pos, int bit) {
  if (bit == 0) {
    value->bits[pos / 32] &= ~(1 << (pos % 32));
  } else {
    value->bits[pos / 32] |= (1 << (pos % 32));
  }
}

void s_scale(s21_decimal* value, int scale) {
  value->bits[3] = (value->bits[3] & (1 << 31)) | (scale << 16);
}
