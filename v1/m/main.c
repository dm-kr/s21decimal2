#include "../s21_decimal.h"

int main() {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  int error = s21_sub(val1, val2, &res);
  print_decimal(val1);
  print_decimal(val2);
  print_decimal(res);
  printf("%d", error);
  printf("\n");
  return 0;
}
