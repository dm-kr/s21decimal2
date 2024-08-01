#include <stdio.h>

#include "../../s21_decimal.h"

void print(s21_decimal a) {
  // printf("%d\n", get_scale(a));
  for (int i = 95; i >= 0; i--) {
    printf("%d", get_bit(a, i));
    if (i % 32 == 0 && i > 0) printf(" ");
  }
  printf("\n");
}

void printh(s21_decimal a) {
  for (int i = 0; i < 4; i++) {
    printf("%X ", a.bits[i]);
  }
  printf("\n");
}

int main() {
  s21_decimal a = {{3221286292, 0, 0, 0}};
  print(a);
  s21_decimal b = bshift(a, RIGHT, 1);
  print(b);
  printf("\n");
  return 0;
}