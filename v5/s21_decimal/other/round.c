#include "./../arithmetic/arithmetic.h"
#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./other.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_other_result code = S21_OTHER_OK;

  if (!result) {
    // Если указатель на decimal является NULL
    code = S21_OTHER_ERROR;
  } else if (!is_correct(value)) {
    // Проверяем, что value является корректными decimal
    code = S21_OTHER_ERROR;
    *result = inf();
  } else {
    // В остальных случаях округляем
    *result = Decimal(0);
    int sign = get_sign(value);
    s21_decimal fractional;
    s21_decimal value_unsigned_truncated;
    // Убираем знак
    s21_decimal value_unsigned = decimal_abs(value);
    // Убираем дробную часть числа
    s21_truncate(value_unsigned, &value_unsigned_truncated);

    // Считаем убранную дробную часть числа
    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);

    // Производим округление, исходя из дробной части числа
    // value_unsigned_truncated = s21_round_banking(value_unsigned_truncated,
    // fractional);

    s21_decimal half = zerofive();

    if (s21_is_greater_or_equal(fractional, half)) {
      // Если дробная часть > 0.5, то увеличиваем целую часть на 1
      *result = bin_add(value_unsigned_truncated, Decimal(1));
    } else {
      // Если дробная часть < 0.5, то оставляем целую часть без изменений
      *result = value_unsigned_truncated;
    }

    // Возвращаем знак
    set_sign(result, sign);
  }

  return code;
}
