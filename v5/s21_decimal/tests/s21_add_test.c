#include "../s21_decimal.h"
#include "s21_decimal_test.h"

static s21_decimal array1[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x80010000}},  // 0.0
    {{0x00000001, 0x00000000, 0x00000000, 0x800E0000}},  // -0.00000000000001
    {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  // 2.5
    {{0x00000183, 0x00000000, 0x00000000, 0x00020000}},  // 3.87
    {{0x14490831, 0x00048E23, 0x00000000, 0x00070000}},  // 128218122.2172721
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x77D5E3AA, 0x0000011C, 0x00000000, 0x00060000}},  // 1221781.218218
    {{0x80000000, 0x80000000, 0x80000000,
      0x801C0000}},  // -3.9614081266355540835774234624
    {{0x80000000, 0x80000000, 0x80000000,
      0x000E0000}},  // 396140812663555.40835774234624
    {{0x00000001, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000001
    {{0x000F4240, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000001000000
    {{0x00000000, 0x00000000, 0x00000000, 0x000E0000}},  // 0.00000000000000
    {{0x00000000, 0x00000000, 0x00000000, 0x000E0000}},  // 0.00000000000000
    {{0x80000000, 0x80000000, 0x80000000,
      0x00000000}},  // 39614081266355540835774234624
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00010000}},  // 7922816251426433759354395033.5
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0x1422CF6C, 0x000001FC, 0x00000000, 0x80030000}},  // -2182181212.012
    {{0x2564B1EA, 0x3927F1F3, 0x041C50D7,
      0x000B0000}},  // 12721717217217217.21821901290
    {{0x0001869F, 0x00000000, 0x00000000, 0x00050000}},  // 0.99999
    {{0x0098967E, 0x00000000, 0x00000000, 0x80060000}},  // -9.999998
    {{0x000000CF, 0x00000000, 0x00000000, 0x00010000}},  // 20.7
    {{0x0707E3C5, 0x002D8D61, 0x00000000, 0x80090000}},  // -12821821.821281221
    {{0x846A4B4C, 0x0000012A, 0x00000000, 0x00080000}},  // 12821.21812812
    {{0x000035A3, 0x00000000, 0x00000000,
      0x00170000}},  // 0.00000000000000000013731
    {{0x79353447, 0x00000004, 0x00000000, 0x00010000}},  // 1921339911.1
    {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950333
    {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950333
    {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950333
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950334
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950334
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950334
};

static s21_decimal array2[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000006, 0x00000000, 0x00000000, 0x000F0000}},  // 0.000000000000006
    {{0x00000064, 0x00000000, 0x00000000, 0x00000000}},  // 100
    {{0x00004DA6, 0x00000000, 0x00000000, 0x00020000}},  // 198.78
    {{0x164214B7, 0x00000028, 0x00000000, 0x00040000}},  // 17217212.1271
    {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  // 2.5
    {{0x00212155, 0x00000000, 0x00000000, 0x00070000}},  // 0.2171221
    {{0x80000000, 0x80000000, 0x80000000,
      0x801C0000}},  //-3.9614081266355540835774234624
    {{0x80000000, 0x80000000, 0x80000000,
      0x000E0000}},  // 396140812663555.40835774234624
    {{0x00000001, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000001
    {{0x000186A0, 0x00000000, 0x00000000,
      0x00140000}},  // 0.00000000000000100000
    {{0x00000000, 0x00000000, 0x00000000, 0x000A0000}},  // 0.0000000000
    {{0x00000000, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000000
    {{0x00000000, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000000
    {{0x00000005, 0x00000000, 0x00000000, 0x00010000}},  // 0.5
    {{0x00000000, 0x00000000, 0x00000000, 0x000A0000}},  // 0.0000000000
    {{0xF96C01C5, 0x0007B6B6, 0x00000000, 0x800B0000}},  //-21712.21821882821
    {{0x00033F4A, 0x00000000, 0x00000000, 0x000C0000}},  // 0.000000212810
    {{0x00000001, 0x00000000, 0x00000000, 0x00050000}},  // 0.00001
    {{0x00000002, 0x00000000, 0x00000000, 0x80060000}},  //-0.000002
    {{0x00003F86, 0x00000000, 0x00000000,
      0x00160000}},  // 0.0000000000000000016262
    {{0x058FEC8A, 0x00000000, 0x00000000, 0x00050000}},  // 933.18282
    {{0x0081787B, 0x00000000, 0x00000000, 0x80080000}},  //-0.08484987
    {{0x0001F8A8, 0x00000000, 0x00000000, 0x00030000}},  // 129.192
    {{0xD927FFFF, 0xE1003B28, 0x00000004,
      0x00140000}},  // 0.89999999999999999999
    {{0x00000005, 0x00000000, 0x00000000, 0x00010000}},  // 0.5
    {{0x00000033, 0x00000000, 0x00000000, 0x00020000}},  // 0.51
    {{0x00000031, 0x00000000, 0x00000000, 0x00020000}},  // 0.49
    {{0x00000005, 0x00000000, 0x00000000, 0x00010000}},  // 0.5
    {{0x00000033, 0x00000000, 0x00000000, 0x00020000}},  // 0.51
    {{0x00000031, 0x00000000, 0x00000000, 0x00020000}},  // 0.49
};

static s21_decimal result[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00010000}},  // 0.0
    {{0x00000004, 0x00000000, 0x00000000, 0x800F0000}},  //-0.000000000000004
    {{0x00000401, 0x00000000, 0x00000000, 0x00010000}},  // 102.5
    {{0x00004F29, 0x00000000, 0x00000000, 0x00020000}},  // 202.65
    {{0x0669F309, 0x00052ABA, 0x00000000, 0x00070000}},  // 145435334.3443721
    {{0x00000023, 0x00000000, 0x00000000, 0x00010000}},  // 3.5
    {{0xAE7C05F9, 0x00000B1C, 0x00000000, 0x00070000}},  // 1221781.4353401
    {{0x4CCCCCCD, 0xB3333333, 0x19999999,
      0x801B0000}},  //-7.922816253271108167154846925
    {{0x4CCCCCCD, 0xB3333333, 0x19999999,
      0x000D0000}},  // 792281625327110.8167154846925
    {{0x00000002, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000002
    {{0x4E81E240, 0x00000918, 0x00000000,
      0x001C0000}},  // 0.0000000000000010000001000000
    {{0x00000000, 0x00000000, 0x00000000, 0x000E0000}},  // 0.00000000000000
    {{0x00000000, 0x00000000, 0x00000000,
      0x001C0000}},  // 0.0000000000000000000000000000
    {{0x80000000, 0x80000000, 0x80000000,
      0x00000000}},  // 39614081266355540835774234624
    {{0x9999999A, 0x99999999, 0x19999999,
      0x00000000}},  // 7922816251426433759354395034
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0x3015EDC5, 0xD46A37C7, 0x0000000B,
      0x800B0000}},  //-2182202924.23021882821
    {{0x75F2326E, 0x3B8F737F, 0x291B2868,
      0x000C0000}},  // 12721717217217217.218219225710
    {{0x000186A0, 0x00000000, 0x00000000, 0x00050000}},  // 1.00000
    {{0x00989680, 0x00000000, 0x00000000, 0x80060000}},  //-10.000000
    {{0x03603F86, 0x7E1382FF, 0x00002BD5,
      0x00160000}},  // 20.7000000000000000016262
    {{0xC1001525, 0x002D8C87, 0x00000000, 0x80090000}},  //-12820888.638461221
    {{0x83E8D2D1, 0x0000012A, 0x00000000, 0x00080000}},  // 12821.13327825
    {{0x828035A3, 0x3C3F28D0, 0x000AAFBF,
      0x00170000}},  // 129.19200000000000000013731
    {{0x9F400000, 0x563581D8, 0x3E14F385,
      0x00130000}},  // 1921339912.0000000000000000000
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950334
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950334
    {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950333
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950334
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950334
};

static s21_decimal error_array1[] = {
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00010000}},  // 7922816251426433759354395033.5
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00020000}},  // 792281625142643375935439503.35
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // -79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // -79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80040000}},  // -7922816251426433759354395.0335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80080000}},  // -792281625142643375935.43950335
};

static s21_decimal error_array2[] = {
    {{0x00000006, 0x00000000, 0x00000000, 0x00010000}},  // 0.6
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0xFFF0BDBF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593542950335
    {{0xFFFE7906, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543850246
    {{0x00000007, 0x00000000, 0x00000000, 0x80010000}},  //-0.7
    {{0x0000000A, 0x00000000, 0x00000000, 0x80010000}},  //-1.0
    {{0xFF67697F, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  //-79228162514264337593533950335
    {{0xFF642CF2, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  //-79228162514264337593533738226
};

static int error_result[] = {
    1, 1, 1, 1, 2, 2, 2, 2,
};

START_TEST(test_add) {
  s21_decimal tmp = {{0, 0, 0, 0}};
  int code = s21_add(array1[_i], array2[_i], &tmp);
  ck_assert_int_eq(s21_is_equal(tmp, result[_i]), 1);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_add_with_error) {
  s21_decimal empty = {{0, 0, 0, 0}};
  int code = s21_add(error_array1[_i], error_array2[_i], &empty);
  ck_assert_int_eq(code, error_result[_i]);
}
END_TEST

Suite *suite_add(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("ADD");
  tc_core = tcase_create("Core");

  tcase_add_loop_test(tc_core, test_add, 0,
                      sizeof(array1) / sizeof(s21_decimal));
  tcase_add_loop_test(tc_core, test_add_with_error, 0,
                      sizeof(error_array1) / sizeof(s21_decimal));

  suite_add_tcase(s, tc_core);

  return s;
}
