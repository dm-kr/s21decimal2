#include "../s21_decimal.h"
#include "s21_decimal_test.h"

static s21_decimal array1[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00030000}},  // 0.000
    {{0x00000000, 0x00000000, 0x00000000, 0x800A0000}},  // 0.0000000000
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  // -1
    {{0x0000000C, 0x00000000, 0x00000000, 0x80010000}},  // -1.2
    {{0x000000F3, 0x00000000, 0x00000000, 0x00020000}},  // 2.43
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950334
    {{0x000007CF, 0x00000000, 0x00000000, 0x00000000}},  // 1999
    {{0x0000000F, 0x00000014, 0x00000000, 0x800A0000}},  // -8.5899345935
    {{0x0000000F, 0x00000014, 0x0000072E,
      0x800A0000}},  // -3390511560756.4055216143
    {{0x0000000F, 0x00000014, 0x0000072E,
      0x00020000}},  // 339051156075640552161.43
    {{0x99362457, 0x0007AE79, 0x00000000, 0x00080000}},  // 21621621.21712727
    {{0x99362457, 0x0007AE79, 0x00000000, 0x00080000}},  // 21621621.21712727
    {{0x99362457, 0x0007AE79, 0x00000000, 0x00080000}},  // 21621621.21712727
    {{0x2113B8B0, 0x00000917, 0x00000000, 0x80070000}},  // -999494.3838384
    {{0x2113B8B0, 0x00000917, 0x00000000, 0x80070000}},  // -999494.3838384
    {{0x2113B8B0, 0x00000917, 0x00000000, 0x80070000}},  // -999494.3838384
    {{0x00000086, 0x00000054, 0x00000013,
      0x00010000}},  // 35048813776125873370.2
    {{0x00000085, 0x00000054, 0x00000013,
      0x00010000}},  // 35048813776125873370.1
    {{0x000011EB, 0x00000000, 0x00000000, 0x80010000}},  // -458.7
    {{0x00000000, 0x00000000, 0x00000000, 0x00020000}},  // 0.00
    {{0x0000007B, 0x00000000, 0x00000000, 0x00070000}},  // 0.0000123
    {{0x00003225, 0x00000000, 0x00000000, 0x80020000}},  // -128.37
    {{0x07A5B45C, 0x00000000, 0x00000000, 0x00050000}},  // 1283.00124
    {{0x0005D9E0, 0x00000000, 0x00000000, 0x80030000}},  // -383.456
    {{0x0005D9E0, 0x00000000, 0x00000000, 0x80030000}},  // -383.456
    {{0x0005D9E0, 0x00000000, 0x00000000, 0x80030000}},  // -383.456
    {{0x39608B53, 0x0000001C, 0x00000000, 0x00050000}},  // 1212217.12723
    {{0x39608B53, 0x0000001C, 0x00000000, 0x00050000}},  // 1212217.12723
    {{0x39608B53, 0x0000001C, 0x00000000, 0x00050000}},  // 1212217.12723
    {{0x000000B6, 0x00000000, 0x00000000, 0x80010000}},  // -18.2
    {{0x000000C2, 0x00000000, 0x00000000, 0x80010000}},  // -19.4
    {{0x000049E2, 0x00000000, 0x00000000, 0x00020000}},  // 189.14
    {{0x00193D97, 0x00000000, 0x00000000, 0x00030000}},  // 1654.167
    {{0x0012D795, 0x00000000, 0x00000000, 0x00030000}},  // 1234.837
    {{0x00003EFB, 0x00000000, 0x00000000, 0x80030000}},  // -16.123
    {{0x000046CB, 0x00000000, 0x00000000, 0x80030000}},  // -18.123
    {{0x00004347, 0x00000000, 0x00000000, 0x80030000}},  // -17.223
    {{0x000042E3, 0x00000000, 0x00000000, 0x80030000}},  // -17.123
    {{0x000042E2, 0x00000000, 0x00000000, 0x80030000}},  // -17.122
    {{0x000046CB, 0x00000000, 0x00000000, 0x80030000}},  // -18.123
    {{0x000046CA, 0x00000000, 0x00000000, 0x80030000}},  // -18.122
    {{0x000046CC, 0x00000000, 0x00000000, 0x80030000}},  // -18.124
    {{0x00003EFB, 0x00000000, 0x00000000, 0x00030000}},  // 16.123
    {{0x000046CB, 0x00000000, 0x00000000, 0x00030000}},  // 18.123
    {{0x00004347, 0x00000000, 0x00000000, 0x00030000}},  // 17.223
    {{0x000042E3, 0x00000000, 0x00000000, 0x00030000}},  // 17.123
    {{0x000042E2, 0x00000000, 0x00000000, 0x00030000}},  // 17.122
    {{0x000046CB, 0x00000000, 0x00000000, 0x00030000}},  // 18.123
    {{0x000046CA, 0x00000000, 0x00000000, 0x00030000}},  // 18.122
    {{0x000046CC, 0x00000000, 0x00000000, 0x00030000}},  // 18.124
    {{0x00000000, 0x00000000, 0x00000000, 0x80030000}},  // 0.000
    {{0x00003C28, 0x00000000, 0x00000000, 0x80020000}},  // -154.00
    {{0x0000009A, 0x00000000, 0x00000000, 0x00000000}},  // 154
    {{0x00003C28, 0x0000000D, 0x0000000B,
      0x80020000}},  // -2029141848666396580.24
    {{0x0001E0F4, 0x00000000, 0x00000000, 0x00030000}},  // 123.124
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
};

static s21_decimal array2[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00010000}},  // 0.0
    {{0x00000000, 0x00000000, 0x00000000, 0x00030000}},  // 0.000
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  // -1
    {{0x00000070, 0x00000000, 0x00000000, 0x80020000}},  // -1.12
    {{0x000000F4, 0x00000000, 0x00000000, 0x00030000}},  // 0.244
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950334
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0x00004E20, 0x00000000, 0x00000000, 0x00000000}},  // 20000
    {{0x0000000D, 0x00000014, 0x00000000, 0x800A0000}},  // -8.5899345933
    {{0x0000000F, 0x00000013, 0x0000072E,
      0x800A0000}},  // -3390511560755.9760248847
    {{0x0000000F, 0x00000014, 0x0000072F,
      0x00020000}},  // 339235623516377647677.59
    {{0x99362457, 0x0007AE79, 0x00000000, 0x00080000}},  // 21621621.21712727
    {{0x99362458, 0x0007AE79, 0x00000000, 0x00080000}},  // 21621621.21712728
    {{0x99362456, 0x0007AE79, 0x00000000, 0x00080000}},  // 21621621.21712726
    {{0x2113B8B0, 0x00000917, 0x00000000, 0x80070000}},  // -999494.3838384
    {{0x2113B8AF, 0x00000917, 0x00000000, 0x80070000}},  // -999494.3838383
    {{0x2113B8B1, 0x00000917, 0x00000000, 0x80070000}},  // -999494.3838385
    {{0x00003458, 0x00000054, 0x00000013,
      0x00030000}},  // 350488137761258746.968
    {{0x00003458, 0x00000054, 0x00000013,
      0x00030000}},  // 350488137761258746.968
    {{0x000011EB, 0x00000000, 0x00000000, 0x80020000}},  // -45.87
    {{0x00000086, 0x00000000, 0x00000000, 0x00010000}},  // 13.4
    {{0x00000000, 0x00000000, 0x00000000, 0x00010000}},  // 0.0
    {{0x00003225, 0x00000000, 0x00000000, 0x80020000}},  // -128.37
    {{0x001393BA, 0x00000000, 0x00000000, 0x00030000}},  // 1283.002
    {{0x0005D9E0, 0x00000000, 0x00000000, 0x80030000}},  // -383.456
    {{0x0005D9DF, 0x00000000, 0x00000000, 0x80030000}},  // -383.455
    {{0x0005D9E1, 0x00000000, 0x00000000, 0x80030000}},  // -383.457
    {{0x39608B53, 0x0000001C, 0x00000000, 0x00050000}},  // 1212217.12723
    {{0x39608B52, 0x0000001C, 0x00000000, 0x00050000}},  // 1212217.12722
    {{0x39608B54, 0x0000001C, 0x00000000, 0x00050000}},  // 1212217.12724
    {{0x000000B5, 0x00000000, 0x00000000, 0x80010000}},  // -18.1
    {{0x000000C2, 0x00000000, 0x00000000, 0x00010000}},  // 19.4
    {{0x000049E2, 0x00000000, 0x00000000, 0x80020000}},  // -189.14
    {{0x00193D97, 0x00000000, 0x00000000, 0x00030000}},  // 1654.167
    {{0x0012D3AD, 0x00000000, 0x00000000, 0x00030000}},  // 1233.837
    {{0x000042E3, 0x00000000, 0x00000000, 0x80030000}},  // -17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x80030000}},  // -17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x80030000}},  // -17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x80030000}},  // -17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x80030000}},  // -17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x80030000}},  // -17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x80030000}},  // -17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x80030000}},  // -17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x00030000}},  // 17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x00030000}},  // 17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x00030000}},  // 17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x00030000}},  // 17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x00030000}},  // 17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x00030000}},  // 17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x00030000}},  // 17.123
    {{0x000042E3, 0x00000000, 0x00000000, 0x00030000}},  // 17.123
    {{0x00000000, 0x00000000, 0x00000000, 0x00040000}},  // 0.0000
    {{0x0000009A, 0x00000000, 0x00000000, 0x80000000}},  // -154
    {{0x00003C28, 0x00000000, 0x00000000, 0x00020000}},  // 154.00
    {{0x0000009A, 0x0000000D, 0x0000000B,
      0x80020000}},  // -2029141848666396427.78
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00070000}},  // 0.0000000
};

static int result[] = {
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1,
    1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
};

static s21_decimal error_array1[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x81000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
};

static s21_decimal error_array2[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00001000}},  // 0
};

static int error_result[] = {
    -1,
    -1,
};

START_TEST(test_is_not_equal) {
  int code = s21_is_not_equal(array1[_i], array2[_i]);
  ck_assert_int_eq(code, result[_i]);
}
END_TEST

START_TEST(test_is_not_equal_with_error) {
  int code = s21_is_not_equal(error_array1[_i], error_array2[_i]);
  ck_assert_int_eq(code, error_result[_i]);
}
END_TEST

Suite *suite_is_not_equal(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("IS_NOT_EQUAL");
  tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_is_not_equal, 0,
                      sizeof(array1) / sizeof(s21_decimal));
  tcase_add_loop_test(tc_core, test_is_not_equal_with_error, 0,
                      sizeof(error_array1) / sizeof(s21_decimal));
  suite_add_tcase(s, tc_core);

  return s;
}
