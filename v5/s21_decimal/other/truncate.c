#include <stdlib.h>

#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./other.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int code = 1;
  if (result && is_correct(value)) {
    code = 0;
    int scale = get_scale(value);
    big_decimal tmp = tobd(value);
    clear_service(&tmp.decimals[0]);
    clear_service(&tmp.decimals[1]);
    tmp = bd_bin_div(tmp, tobd(ten_pow(scale)), NULL);
    *result = tmp.decimals[0];
    set_sign(result, get_sign(value));
  }
  return code;
}
