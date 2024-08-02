#include "./../helpers/helpers.h"
#include "./other.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int code = 1;
  if (result) {
    *result = value;
    set_sign(result, !get_sign(*result));
    if (is_correct(value)) code = 0;
  }
  return code;
}
