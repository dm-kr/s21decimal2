#include "./../arithmetic/arithmetic.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./other.h"

/**
 * @brief Округляет value до ближайшего целого числа в сторону отрицательной
 * бесконечности.
 *
 * @param value округляемое число
 * @param result указатель, куда будет записан результат
 * @return int код ошибки:
 *      0 - OK
 *      1 - ошибка вычисления
 */
int s21_floor(s21_decimal value, s21_decimal *result) {
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

    // Если дробная часть была больше нуля и число было отрицательным, то
    // прибавляем 1
    if (sign == 1 && s21_is_greater(fractional, Decimal(0))) {
      s21_add(value_unsigned_truncated, Decimal(1), &value_unsigned_truncated);
    }

    *result = value_unsigned_truncated;
    // Возвращаем знак
    set_sign(result, sign);
  }

  return code;
}
