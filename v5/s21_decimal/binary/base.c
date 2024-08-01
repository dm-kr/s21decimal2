#include "./../types.h"

int get_bit(s21_decimal value, int index) {
  return (value.bits[index / INT_SIZE] & (1 << (index % INT_SIZE))) != 0;
}

s21_decimal set_bit(s21_decimal value, int index) {
  value.bits[index / INT_SIZE] |= 1 << index % INT_SIZE;
  return value;
}

int get_significants(s21_decimal value) {
  int result = -1;
  for (int i = MAX_BITS - 1; i >= 0 && result == -1; i--) {
    if (get_bit(value, i)) result = i;
  }
  return result;
}
