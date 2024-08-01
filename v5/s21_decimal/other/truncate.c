#include <stdlib.h>

#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./other.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_other_result code = S21_OTHER_OK;
  if (!result) {
    code = S21_OTHER_ERROR;
  } else if (!is_correct(value)) {
    code = S21_OTHER_ERROR;
    *result = inf();
  } else {
    *result = Decimal(0);
    int power = get_scale(value);
    big_decimal tmp = tobd(value);
    clear_service(&tmp.decimals[0]);
    clear_service(&tmp.decimals[1]);
    tmp = bd_bin_div(tmp, tobd(ten_pow(power)), NULL);
    *result = tmp.decimals[0];
    if (get_sign(value) == 1) {
      set_sign(result, 1);
    }
  }
  return code;
}
