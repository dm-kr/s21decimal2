#ifndef SRC_S21_DECIMAL_TYPES_H_
#define SRC_S21_DECIMAL_TYPES_H_

typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

typedef struct big_decimal {
  s21_decimal decimals[2];
} big_decimal;

#define MAX_BITS 128
#define INT_SIZE 32
#define BASE_SIZE 96

typedef union service_bits {
  int bits;
  struct {
    unsigned int empty2 : 16;
    unsigned int scale : 8;
    unsigned int empty1 : 7;
    unsigned int sign : 1;
  } parts;
} service_bits;

#endif  //  SRC_S21_DECIMAL_TYPES_H_
