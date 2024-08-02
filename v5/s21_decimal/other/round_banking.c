#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./other.h"

s21_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional) {
  s21_decimal half = zerofive();
  s21_decimal result;
  if (s21_is_equal(fractional, half)) {
    if (is_even(integral)) {
      result = integral;
    } else {
      result = bin_add(integral, Decimal(1));
    }
  } else if (s21_is_greater(fractional, half)) {
    result = bin_add(integral, Decimal(1));
  } else {
    result = integral;
  }
  return result;
}
