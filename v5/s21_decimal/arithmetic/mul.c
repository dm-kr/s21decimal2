#include <stdlib.h>

#include "./../binary/binary.h"
#include "./../comparison/comparison.h"
#include "./../helpers/helpers.h"
#include "./../other/other.h"
#include "./arithmetic.h"
/**
 * @brief Умножает value_1 на value_2 и записывает результат в result
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первый множитель
 * @param value_2 второй множитель
 * @param result произведение
 * @return int код ошибки:
 * 0 - OK
 * 1 - число слишком велико или равно бесконечности
 * 2 - число слишком мало или равно отрицательной бесконечности
 * 3 - деление на 0
 * 4 - некорректные входные данные
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;

  if (!result) {
    // Если указатель на decimal является NULL
    code = S21_ARITHMETIC_ERROR;
  } else if (!is_correct(value_1) || !is_correct(value_2)) {
    // Проверяем, что value_1 и value_2 являются корректными decimal
    code = S21_ARITHMETIC_ERROR;
    *result = inf();
  } else {
    // В остальных случаях считаем произведение
    *result = Decimal(0);
    s21_decimal res = Decimal(0);

    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);

    if (sign1 == 0 && sign2 == 0) {
      // Если оба множителя положительные
      // вызываем перемножение
      // v1 = 2; v2 = 1;
      // v1 * v2 = 2 * 1 = v2 * v1
      // v1 = 1; v2 = 2;
      // v1 * v2 = 1 * 2 = v2 * v1
      code = s21_mul_handle(value_1, value_2, &res);
    } else if (sign1 == 0 && sign2 == 1) {
      // Если первый - положительный, второй - отрицательный
      // вызываем перемножение (используя abs), у результата меняем знак
      // v1 = 2; v2 = -1;
      // v1 * v2 = 2 * -1 = - (2 * 1) = -(v1 * abs(v2))
      // v1 = 2; v2 = -3;
      // v1 * v2 = 2 * -3 = - (2 * 3) = -(v1 * abs(v2))
      code = s21_mul_handle(value_1, decimal_abs(value_2), &res);
      s21_negate(res, &res);
    } else if (sign1 == 1 && sign2 == 0) {
      // Если первый - отрицательный, второй - положительный
      // вызываем перемножение (используя abs), у результата меняем знак
      // v1 = -2; v2 = 1;
      // v1 * v2 = -2 * 1 = -(2 * 1) = -(abs(v1) * v2)
      // v1 = -1; v2 = 2;
      // v1 * v2 = -1 * 2 = -(1 * 2) = -(abs(v1) * v2)
      code = s21_mul_handle(decimal_abs(value_1), value_2, &res);
      s21_negate(res, &res);
    } else if (sign1 == 1 && sign2 == 1) {
      // Если оба множителя отрицательные
      // вызываем перемножение (используя abs)
      // v1 = -2; v2 = -1;
      // v1 * v2 = -2 * -1 = - -(2 * 1) = 2 * 1 = abs(v1) * abs(v2)
      // v1 = -1; v2 = -2;
      // v1 * v2 = -1 * -2 = - -(1 * 2) = 1 * 2 = abs(v1) * abs(v2)
      code = s21_mul_handle(decimal_abs(value_1), decimal_abs(value_2), &res);
    }

    if (code == S21_ARITHMETIC_BIG) {
      if (get_sign(res) == 1) {
        code = S21_ARITHMETIC_SMALL;
      }
    }

    // Обрабатываем ситуацию, что результат получился слишком маленький (0 < |x|
    // < 1e-28)
    if (code == S21_ARITHMETIC_OK && s21_is_not_equal(value_1, Decimal(0)) &&
        s21_is_not_equal(value_2, Decimal(0)) &&
        s21_is_equal(res, Decimal(0))) {
      code = S21_ARITHMETIC_SMALL;
    }

    *result = res;
  }

  return code;
}

/**
 * @brief Вспомогательная функция, которая осуществляет умножение двух
 * положительных чисел decimal
 *
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @param value_1 первый множитель
 * @param value_2 второй множитель
 * @param result произведение
 * @return int код ошибки, для передачи в родительскую функцию (и последующей
 * обработки)
 */
int s21_mul_handle(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  s21_arithmetic_result code = S21_ARITHMETIC_OK;
  int power1 = get_scale(value_1);
  int power2 = get_scale(value_2);

  // зануляем степени чисел (степени получим в конце, анализируя входные данные)
  clear_service(&value_1);
  clear_service(&value_2);

  // Перемножаем множители без степеней как два огромных целых числа
  big_decimal res = bd_bin_mul(tobd(value_1), value_2);

  // Рассчитываем, на сколько необходимо поделить результат, чтобы вписать его в
  // 96бит числа decimal
  int shift = s21_int256_get_shift_to_decimal(res);
  // Рассчитываем степень будущего результата
  int res_power = power1 + power2 - shift;

  if (res_power < 0) {
    // Анализируем степень результата на корректность
    code = S21_ARITHMETIC_BIG;
    *result = inf();
  } else {
    // Если результат надо делить более, чем на 10^28, то уменьшаем его, чтобы
    // далее делить на 10^28
    while (shift > 28) {
      res = bd_bin_div(res, tobd(Decimal(10)), NULL);
      --shift;
    }

    // Если слишком много цифр после запятой получается в результате, то
    // корректируем результат
    if (res_power > 28) {
      big_decimal tmp = res;
      int tmp_power = res_power;
      while (tmp_power > 28) {
        tmp = bd_bin_div(tmp, tobd(Decimal(10)), NULL);
        --tmp_power;
      }
      shift = res_power - tmp_power + shift;
      res_power = tmp_power;
    }

    big_decimal remainder = tobd(Decimal(0));
    big_decimal powerten = tobd(ten_pow(shift));

    // Уменьшаем результат, чтобы он поместился в 96бит числа decimal
    // remainder - остаток от деления при этом
    res = bd_bin_div(res, powerten, &remainder);
    // Устанавливаем для остатка степень, чтобы выполнить банковское округление
    // чисел decimal
    set_scale(&remainder.decimals[0], shift);
    // Выполняем банковское округления результата, исходя из остатка от деления
    // remainder
    res.decimals[0] = s21_round_banking(res.decimals[0], remainder.decimals[0]);
    // Устанавливаем степень результата
    set_scale(&res.decimals[0], res_power);

    // Анализируем результат на корректность (переполнение)
    if (!is_null(res.decimals[1]) || !is_correct(res.decimals[0])) {
      code = S21_ARITHMETIC_BIG;
      *result = inf();
    } else {
      *result = res.decimals[0];
    }
  }

  return code;
}
