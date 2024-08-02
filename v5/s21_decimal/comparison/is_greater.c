#include "./comparison.h"

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  return s21_is_less(value2, value1);
}
