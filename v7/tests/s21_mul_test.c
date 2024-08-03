#include "../s21_decimal.h"
#include "s21_decimal_test.h"

static s21_decimal array1[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
    {{0x55555555, 0x55555555, 0x0, 0x0}},
    {{0x55555555, 0x55555555, 0x55555555, 0x150000}},
    {{0x0000007B, 0x00000000, 0x00000000, 0x80000000}},
};

static s21_decimal array2[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
    {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}},
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}},
    {{0x000001B0, 0x00000000, 0x00000000, 0x80000000}},
};

static s21_decimal result[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},
    {{0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0xA0000}},
    {{0xADCFA172, 0x67336914, 0x439BA7FC, 0x80140000}},
    {{0x0000CF90, 0x00000000, 0x00000000, 0x00000000}},
};

static s21_decimal error_array1[] = {
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80080000}},  // -792281625142643375935.43950335
};

static s21_decimal error_array2[] = {
    {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 2
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}},
    {{0xFF642CF2, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593533738226
};

static int error_result[] = {
    1,
    1,
    2,
};

START_TEST(test_mul) {
  s21_decimal tmp = {{0, 0, 0, 0}};
  int code = s21_mul(array1[_i], array2[_i], &tmp);
  ck_assert_int_eq(s21_is_equal(tmp, result[_i]), 1);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_mul_with_error) {
  s21_decimal empty = {{0, 0, 0, 0}};
  int code = s21_mul(error_array1[_i], error_array2[_i], &empty);
  ck_assert_int_eq(code, error_result[_i]);
}
END_TEST

Suite *suite_mul(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("MUL");
  tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_mul, 0,
                      sizeof(array1) / sizeof(s21_decimal));
  tcase_add_loop_test(tc_core, test_mul_with_error, 0,
                      sizeof(error_array1) / sizeof(s21_decimal));
  suite_add_tcase(s, tc_core);

  return s;
}
