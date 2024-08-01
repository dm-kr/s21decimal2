#include <string.h>

#include "./../binary/binary.h"
#include "./helpers.h"

void clear(s21_decimal *decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}

void clear_service(s21_decimal *value) { value->bits[3] = 0; }

s21_decimal Decimal(int number) {
  s21_decimal result;
  clear(&result);
  result.bits[0] = number;
  return result;
}

s21_decimal ten_pow(int pow) { return ten_pows[pow]; }

s21_decimal zerofive(void) {
  s21_decimal result = {{0x5, 0x0, 0x0, 0x10000}};
  return result;
}

s21_decimal min_decimal(void) {
  s21_decimal result = {{0x1, 0x0, 0x0, 0x1C0000}};
  return result;
}

s21_decimal max_decimal(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  return result;
}

s21_decimal max_int(void) {
  s21_decimal result = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};

  return result;
}

s21_decimal min_int(void) {
  s21_decimal result = {{0x80000000, 0x0, 0x0, 0x80000000}};

  return result;
}

big_decimal tobd(s21_decimal value) {
  big_decimal result;
  result.decimals[0] = value;
  result.decimals[1] = Decimal(0);
  return result;
}

s21_decimal inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  return result;
}
