#include "./../helpers/helpers.h"
#include "./binary.h"

s21_decimal bshift(s21_decimal value, int dir, int amount) {
  s21_decimal result = value;
  for (int count = 0; count < amount; count++) {
    int temp = 0;
    int carry = 0;
    for (int i = 0; i < 4; i++) {
      int j = dir ? i + 1 : 3 - i;
      temp = get_bit(result, INT_SIZE * j - dir);
      if (dir) {
        result.bits[i] <<= 1;
        if (carry) result = set_bit(result, INT_SIZE * i);
      } else {
        unsigned int temp = result.bits[j];
        result.bits[j] = temp >> 1;
        if (carry) result = set_bit(result, INT_SIZE * (j + 1) - 1);
      }
      carry = temp;
    }
  }
  return result;
}

big_decimal bdshift(big_decimal value, int dir, int amount) {
  big_decimal result = value;
  for (int count = 0; count < amount; count++) {
    int j = dir ? MAX_BITS - 1 : 0;
    int bit = get_bit(result.decimals[1 - dir], j);
    result.decimals[0] = bshift(result.decimals[0], dir, 1);
    result.decimals[1] = bshift(result.decimals[1], dir, 1);
    if (bit) {
      result.decimals[dir] =
          set_bit(result.decimals[dir], dir ? 0 : MAX_BITS - 1);
    }
  }
  return result;
}