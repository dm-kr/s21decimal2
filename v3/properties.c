#include "s21_decimal.h"

int sign(s21_decimal value) { return (value.bits[3] >> 31) != 0; }

int bit(s21_decimal value, int pos) {
  return ((value.bits[pos / 32] & (1 << pos % 32)) != 0);
}

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

int bsign(bd value) { return (value.bits[8] >> 31) != 0; }

int bbit(bd value, int pos) {
  return ((value.bits[pos / 32] & (1 << pos % 32)) != 0);
}

int bscale(bd value) { return (value.bits[8] & 0xFF0000) >> 16; }

void bs_sign(bd* value, unsigned int sign) { bs_bit(value, 287, sign != 0); }

void bs_bit(bd* value, int pos, int bit) {
  if (bit == 0) {
    value->bits[pos / 32] &= ~(1 << (pos % 32));
  } else {
    value->bits[pos / 32] |= (1 << (pos % 32));
  }
}

void bs_scale(bd* value, int scale) {
  value->bits[8] = (value->bits[8] & (1 << 31)) | (scale << 16);
}
