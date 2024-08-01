#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./arithmetic.h"

void s21_decimal_leveling(s21_decimal value_1, s21_decimal value_2,
                          big_decimal *value_1l, big_decimal *value_2l) {
  int power1 = get_scale(value_1);
  int power2 = get_scale(value_2);
  s21_decimal tmp1 = value_1;
  s21_decimal tmp2 = value_2;

  clear_service(&tmp1);
  clear_service(&tmp2);

  if (power1 > power2) {
    *value_1l = tobd(tmp1);
    *value_2l = bd_bin_mul(tobd(tmp2), ten_pow(power1 - power2));
  } else if (power1 < power2) {
    *value_1l = bd_bin_mul(tobd(tmp1), ten_pow(power2 - power1));
    *value_2l = tobd(tmp2);
  } else {
    *value_1l = tobd(tmp1);
    *value_2l = tobd(tmp2);
  }
}
