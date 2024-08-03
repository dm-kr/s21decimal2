#include "s21_decimal_test.h"

int main(void) {
  Suite *list_cases[] = {suite_add(),
                         suite_div(),
                         suite_mul(),
                         suite_sub(),

                         suite_is_less(),
                         suite_is_less_or_equal(),
                         suite_is_greater(),
                         suite_is_greater_or_equal(),
                         suite_is_equal(),
                         suite_is_not_equal(),

                         suite_from_int_to_decimal(),
                         suite_from_float_to_decimal(),
                         suite_from_decimal_to_int(),
                         suite_from_decimal_to_float(),

                         suite_floor(),
                         suite_negate(),
                         suite_round(),
                         suite_truncate(),

                         NULL};
  int n = 0;
  int f = 0;
  for (int i = 0; list_cases[i]; i++) {
    fprintf(stderr,
            "------------------------------------------------------------------"
            "------------\n");
    SRunner *runner = srunner_create(list_cases[i]);
    srunner_run_all(runner, CK_NORMAL);
    n += srunner_ntests_run(runner);
    f += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  fprintf(stdout,
          "------------------------------------------------------------------"
          "------------\n");
  printf(
      "----------------------- ALL TESTS: % 4d | FAILED: %-0"
      "4d -----------------------\n",
      n, f);
  fprintf(stdout,
          "------------------------------------------------------------------"
          "------------\n");
  return 0;
}
