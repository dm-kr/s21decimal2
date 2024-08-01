#include "./helpers.h"

#include <stdio.h>
#include <stdlib.h>

#include "./../binary/binary.h"

int is_correct(s21_decimal value) {
  int code = 1;
  if (get_empty1(value) != 0 || get_empty2(value) != 0) {
    code = 0;
  } else {
    int scale = get_scale(value);
    if (scale < 0 || scale > 28) {
      code = 0;
    }
  }
  return code;
}

int get_sign(s21_decimal value) {
  service_bits service;
  service.bits = value.bits[3];
  return service.parts.sign;
}

int get_scale(s21_decimal value) {
  service_bits service;
  service.bits = value.bits[3];
  return service.parts.scale;
}

int get_empty1(s21_decimal value) {
  service_bits service;
  service.bits = value.bits[3];
  return service.parts.empty1;
}

int get_empty2(s21_decimal value) {
  service_bits service;
  service.bits = value.bits[3];
  return service.parts.empty2;
}

void set_sign(s21_decimal *value, int sign) {
  service_bits service;
  service.bits = value->bits[3];
  if (sign == 0) {
    service.parts.sign = 0;
  } else {
    service.parts.sign = 1;
  }
  value->bits[3] = service.bits;
}

void set_scale(s21_decimal *decimal, int scale) {
  service_bits service;
  service.bits = decimal->bits[3];
  service.parts.scale = scale;

  decimal->bits[3] = service.bits;
}

int is_even(s21_decimal value) { return (value.bits[0] & 1) != 1; }
