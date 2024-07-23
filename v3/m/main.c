#include "../s21_decimal.h"

int b(unsigned int x, int pos) { return (x & (1 << pos)) != 0; }

void pr(unsigned int x) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", b(x, i));
  }
  printf("\n");
}

unsigned int toa(unsigned int x, int *error) {
  if (x == UINT_MAX) *error = 2;
  x = ~x + 1;
  return x;
}

unsigned int add(unsigned int x, unsigned int y, int xs, int ys, int *err) {
  int error = 0;
  unsigned int c = 0;
  if (xs < ys) x = toa(x, &error);
  if (ys < xs) y = toa(y, &error);
  while (y > 0) {
    c = x & y;
    x = x ^ y;
    y = c << 1;
  }
  if (!(xs | ys)) {
    error |= c != 0;
  } else if (xs && ys) {
    error = error != 0 ? error : 2 * (c != 0);
  }
  *err = error;
  return x;
}

unsigned int mul(unsigned int x, unsigned int y, int xs, int ys, int *err) {
  unsigned int res = 0;
  unsigned int temp = x;
  for (int i = 0; i < 32 && *err == 0; i++) {
    if (b(y, i)) {
      res = add(res, temp, 0, 0, err);
    }
    temp <<= 1;
  }
  return res * xs * ys;
}

int main() {
  // unsigned int x = 3000000000;
  // unsigned int y = 4;
  // int error = 0;
  // unsigned int res = mul(x, y, 1, 1, &error);
  // printf("%u", res);

  //====32=bit=shit====//

  s21_decimal a = Decimal(122142);
  s_scale(&a, 1);
  print(a);
  bd b = tobd(a);
  s21_decimal c = Decimal(0);
  int error = tos21(b, &c);
  print(c);
  printf("Error: %d\n", error);

  // s21_decimal a = Decimal(111111);
  // s21_decimal b = Decimal(1);
  // s21_decimal c = Decimal(0);
  // s_scale(&a, 3);
  // s_scale(&b, 2);
  // int error = s21_mul(a, b, &c);
  // float x = 0;
  // s21_from_decimal_to_float(c, &x);
  // printf("%f -> %d\n", x, error);

  //===========================//

  // s21_decimal a = Decimal(0);
  // float f = -0.000001;
  // printf("%g\n", f);
  // int error = s21_from_float_to_decimal(f, &a);
  // print(a);
  // printf("\nError: %d\n", error);
  // __int8_t a = 5;
  // printf("%d\n", a);
  // // 000001
  // // a <<= 10;
  // a >>= 2;
  // printf("%d\n", a);

  // int x = 1 << 31;
  // printf("%d\n", ~x);

  // return 0;
}
