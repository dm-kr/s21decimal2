#include "../s21_decimal.h"

int main() {
  s21_decimal a = {{0x00000001, 0x00000000, 0x00000000, 0x800E0000}};
  // s_scale(&a, 1);
  s21_decimal b = {{0x00000006, 0x00000000, 0x00000000, 0x000F0000}};
  print(a);
  print(b);
  s21_decimal c = Decimal(0);
  int err = s21_add(a, b, &c);
  print(c);
  printf("Error: %d\n", err);
  return 0;
}
