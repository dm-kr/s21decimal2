#include "../s21_decimal.h"

int main() {
  s21_decimal a = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
  // s_scale(&a, 1);
  s21_decimal b = {{0x80000000, 0x80000000, 0x80000000, 0x801C0000}};
  s21_decimal test = {{0x4CCCCCCD, 0xB3333333, 0x19999999, 0x801B0000}};
  print(a);
  print(b);
  s21_decimal c = Decimal(0);
  int err = s21_add(a, b, &c);
  print(c);
  print(test);
  printf("Error: %d\n", err);
  return 0;
}
