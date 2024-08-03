#include "s21_decimal.h"

#include "binary.h"
#include "handlers.h"
#include "utility.h"

// ARITHMETIC

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  if (result && is_correct(value_1) && is_correct(value_2)) {
    s21_decimal res = Decimal(0);
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    if (sign1 == 0 && sign2 == 0) {
      code = add_handle(value_1, value_2, &res, 0);
    } else if (sign1 == 0 && sign2 == 1) {
      code = s21_sub(value_1, decimal_abs(value_2), &res);
    } else if (sign1 == 1 && sign2 == 0) {
      code = s21_sub(decimal_abs(value_1), value_2, &res);
      s21_negate(res, &res);
    } else if (sign1 == 1 && sign2 == 1) {
      code = add_handle(decimal_abs(value_1), decimal_abs(value_2), &res, 0);
      s21_negate(res, &res);
    }
    if (get_sign(res) == 1 && code == 1) code = 2;
    *result = res;
  }
  return code;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  if (result && is_correct(value_1) && is_correct(value_2)) {
    s21_decimal res = Decimal(0);
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    if (sign1 == 0 && sign2 == 0) {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        code = add_handle(value_1, value_2, &res, 1);
      } else {
        code = add_handle(value_2, value_1, &res, 1);
        s21_negate(res, &res);
      }
    } else if (sign1 == 0 && sign2 == 1) {
      code = s21_add(value_1, decimal_abs(value_2), &res);
    } else if (sign1 == 1 && sign2 == 0) {
      code = s21_add(decimal_abs(value_1), value_2, &res);
      s21_negate(res, &res);
    } else if (sign1 == 1 && sign2 == 1) {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        code = add_handle(decimal_abs(value_2), decimal_abs(value_1), &res, 1);
      } else {
        code = add_handle(decimal_abs(value_1), decimal_abs(value_2), &res, 1);
        s21_negate(res, &res);
      }
    }
    if (get_sign(res) == 1 && code == 1) code = 2;
    *result = res;
  }
  return code;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  if (result && is_correct(value_1) && is_correct(value_2)) {
    s21_decimal res = Decimal(0);
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    code = mul_handle(decimal_abs(value_1), decimal_abs(value_2), &res);
    if (sign1 ^ sign2) s21_negate(res, &res);
    if (code == 1 && get_sign(res)) code = 2;
    if (code == 0 && s21_is_not_equal(value_1, Decimal(0)) &&
        s21_is_not_equal(value_2, Decimal(0)) &&
        s21_is_equal(res, Decimal(0))) {
      code = 2;
    }
    *result = res;
  }
  return code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  if (result && s21_is_equal(value_2, Decimal(0))) {
    code = 3;
    *result = inf();
  } else if (result && is_correct(value_1) && is_correct(value_2)) {
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    big_decimal bd1;
    big_decimal bd2;
    rescaling(value_1, value_2, &bd1, &bd2);
    big_decimal rem = tobd(Decimal(0));
    big_decimal res;
    res = bd_bin_div(bd1, bd2, &rem);
    if (res.decimals[0].bits[3] != 0 || !is_null(res.decimals[1])) {
      code = 1 + (sign1 != sign2);
      *result = inf();
    } else {
      code = div_handle(bd2, res, rem, result);
      if (sign1 != sign2) set_sign(result, 1);
      if (get_sign(*result) == 1 && code == 1) code = 2;
      if (code == 0 && s21_is_not_equal(value_1, Decimal(0)) &&
          s21_is_equal(*result, Decimal(0))) {
        code = 2;
      }
    }
  }
  return code;
}

// COMPARISON

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  int code = 0;
  int sign1 = get_sign(value1);
  int sign2 = get_sign(value2);
  if (s21_is_equal(value1, Decimal(0)) && s21_is_equal(value2, Decimal(0))) {
    code = 0;
  } else if (sign1 == 1 && sign2 == 0) {
    code = 1;
  } else if (sign1 == 0 && sign2 == 1) {
    code = 0;
  } else if (sign1 == 1 && sign2 == 1) {
    code = is_less_handle(decimal_abs(value2), decimal_abs(value1));
  } else {
    code = is_less_handle(value1, value2);
  }
  return code;
}

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  return s21_is_less(value1, value2) || s21_is_equal(value1, value2);
}

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  return s21_is_less(value2, value1);
}

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  return s21_is_greater(value1, value2) || s21_is_equal(value1, value2);
}

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int code = 1;
  s21_decimal tmp1 = s21_remove_trailing_zeros(value1);
  s21_decimal tmp2 = s21_remove_trailing_zeros(value2);
  if (tmp1.bits[0] == 0 && tmp1.bits[1] == 0 && tmp1.bits[2] == 0 &&
      tmp2.bits[0] == 0 && tmp2.bits[1] == 0 && tmp2.bits[2] == 0) {
    code = 1;
  } else {
    code = tmp1.bits[0] == tmp2.bits[0] && tmp1.bits[1] == tmp2.bits[1] &&
           tmp1.bits[2] == tmp2.bits[2] && tmp1.bits[3] == tmp2.bits[3];
  }

  return code;
}

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  return !s21_is_equal(value1, value2);
}

// CONVERTERS

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int code = 0;
  if (!dst) {
    code = 1;
  } else {
    *dst = Decimal(0);
    set_sign(dst, (unsigned int)src >> 31);
    dst->bits[0] = abs(src);
  }
  return code;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int code = 0;
  if (!dst) {
    code = 1;
  } else if (src == 0.0) {
    *dst = Decimal(0);
  } else if (isinf(src) || isnan(src)) {
    code = 1;
    *dst = inf();
  } else if (fabsf(src) > MAX_FLOAT_TO_CONVERT) {
    code = 1;
    *dst = inf();
  } else if (fabsf(src) < MIN_FLOAT_TO_CONVERT) {
    code = 1;
    *dst = Decimal(0);
  } else {
    char float_string[16];
    sprintf(float_string, "%.6E", fabsf(src));
    *dst = float_string_to_decimal(float_string);
  }
  if (dst) set_sign(dst, signbit(src) != 0);
  return code;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int code = 0;
  if (!dst) {
    code = 1;
  } else if (!is_correct(src)) {
    code = 1;
    *dst = 0;
  } else {
    *dst = 0;
    s21_decimal truncated = Decimal(0);
    s21_truncate(src, &truncated);
    if (s21_is_less(truncated, min_int())) {
      code = 1;
    } else if (s21_is_greater(truncated, max_int())) {
      code = 1;
    } else {
      *dst = truncated.bits[0];
      if (get_sign(src) == 1 && *dst != INT_MIN) *dst = -*dst;
    }
  }
  return code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int code = 0;
  if (!dst) {
    code = 1;
  } else if (!is_correct(src)) {
    code = 1;
    *dst = 0.0;
  } else if (s21_is_equal(src, Decimal(0))) {
    *dst = 0.0;
    if (get_sign(src)) *dst = -0.0;
  } else {
    double tmp = 0.0;
    for (int i = 0; i < BASE_SIZE; i++) {
      if (get_bit(src, i) != 0) {
        tmp += pow(2.0, i);
      }
    }
    tmp /= pow(10, get_scale(src));
    if (get_sign(src)) tmp *= -1.0;
    *dst = (float)tmp;
  }
  return code;
}

// OTHERS

int s21_floor(s21_decimal value, s21_decimal *result) {
  int code = 1;
  if (result && is_correct(value)) {
    code = 0;
    int sign = get_sign(value);
    s21_decimal fractional;
    s21_decimal value_unsigned_truncated;
    s21_decimal value_unsigned = decimal_abs(value);
    s21_truncate(value_unsigned, &value_unsigned_truncated);
    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);
    if (sign == 1 && s21_is_greater(fractional, Decimal(0))) {
      s21_add(value_unsigned_truncated, Decimal(1), &value_unsigned_truncated);
    }
    *result = value_unsigned_truncated;
    set_sign(result, sign);
  }
  return code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int code = 1;
  if (result && is_correct(value)) {
    code = 0;
    int sign = get_sign(value);
    s21_decimal fractional;
    s21_decimal value_unsigned_truncated;
    s21_decimal value_unsigned = decimal_abs(value);
    s21_truncate(value_unsigned, &value_unsigned_truncated);
    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);
    s21_decimal half = zerofive();
    if (s21_is_greater_or_equal(fractional, half)) {
      *result = bin_add(value_unsigned_truncated, Decimal(1));
    } else {
      *result = value_unsigned_truncated;
    }
    set_sign(result, sign);
  }
  return code;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int code = 1;
  if (result && is_correct(value)) {
    code = 0;
    int scale = get_scale(value);
    big_decimal tmp = tobd(value);
    clear_service(&tmp.decimals[0]);
    clear_service(&tmp.decimals[1]);
    tmp = bd_bin_div(tmp, tobd(ten_pow(scale)), NULL);
    *result = tmp.decimals[0];
    set_sign(result, get_sign(value));
  }
  return code;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int code = 1;
  if (result) {
    *result = value;
    set_sign(result, !get_sign(*result));
    if (is_correct(value)) code = 0;
  }
  return code;
}
