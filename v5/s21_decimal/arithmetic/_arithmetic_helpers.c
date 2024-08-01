#include "./../binary/binary.h"
#include "./../helpers/helpers.h"
#include "./arithmetic.h"

int s21_int256_get_shift_to_decimal(big_decimal value) {
  int cnt = 0;

  // Если value содержит только нули, то расчет не производим, резльтат - 0
  if (!(is_null(value.decimals[0]) && is_null(value.decimals[1]))) {
    // Максимальное 96битное число
    big_decimal max = tobd(max_decimal());
    // Находим число, во сколько раз value больше максимального 96битного числа
    big_decimal quotient = bd_bin_div(value, max, (void*)(0));

    // Перебираем все степени 10, чтобы найти ближайшую большую степень, чем
    // quotient Делаем так, потому что это гораздо быстрее, чем делить на 10 в
    // цикле
    while (1) {
      int compare = bin_cmp(quotient.decimals[0], ten_pow(cnt));
      if (compare == -1 || compare == 0) {
        break;
      }
      ++cnt;
    }

    // Проверяем, что value впишется в 96 бит, если поделить на 10 в найденной
    // степени
    big_decimal tmp = bd_bin_div(value, tobd(ten_pow(cnt)), (void*)(0));
    // Если не помещается, то берем следующую степень
    if (!is_null(tmp.decimals[1]) || tmp.decimals[0].bits[3] != 0) {
      ++cnt;
    }
  }

  return cnt;
}

int s21_max(int value_1, int value_2) {
  int result = value_2;
  if (value_1 > value_2) {
    result = value_1;
  }

  return result;
}
