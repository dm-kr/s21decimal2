#include "utility.h"

#include "binary.h"
#include "handlers.h"
#include "s21_decimal.h"

int get_decimal_shift(big_decimal value) {
  int cnt = 0;
  if (!bd_is_null(value)) {
    big_decimal max = tobd(max_decimal());
    big_decimal quotient = bd_bin_div(value, max, NULL);

    while (bin_cmp(quotient.decimals[0], ten_pow(cnt)) > 0) cnt++;
    big_decimal tmp = bd_bin_div(value, tobd(ten_pow(cnt)), NULL);
    if (!is_null(tmp.decimals[1]) || tmp.decimals[0].bits[3] != 0) cnt++;
  }
  return cnt;
}

int s21_max(int value_1, int value_2) {
  return value_1 > value_2 ? value_1 : value_2;
}

s21_decimal decimal_abs(s21_decimal value_1) {
  s21_decimal result = value_1;
  set_sign(&result, 0);
  return result;
}

int calc_fractional(big_decimal *res, big_decimal bd2, big_decimal *rem) {
  int scale = 0;
  int flag = 0;
  big_decimal number = *res;
  big_decimal tmp_rem = *rem;
  big_decimal tmp;
  while ((!is_null((*rem).decimals[0]) || !is_null((*rem).decimals[1])) &&
         scale < 28 && !flag) {
    big_decimal number_stored = number;
    big_decimal rem_stored = tmp_rem;
    number = bd_bin_mul(number, Decimal(10));
    tmp_rem = bd_bin_mul(tmp_rem, Decimal(10));
    tmp = bd_bin_div(tmp_rem, bd2, &tmp_rem);
    number = bd_bin_add(number, tmp);
    if (!is_correct(number.decimals[0])) {
      number = number_stored;
      tmp_rem = rem_stored;
      flag = 1;
    } else {
      scale++;
    }
  }
  *res = number;
  *rem = tmp_rem;
  return scale;
}

void rescaling(s21_decimal d1, s21_decimal d2, big_decimal *bd1,
               big_decimal *bd2) {
  int scale1 = get_scale(d1);
  int scale2 = get_scale(d2);
  s21_decimal tmp1 = d1;
  s21_decimal tmp2 = d2;
  clear_service(&tmp1);
  clear_service(&tmp2);
  *bd1 = tobd(tmp1);
  *bd2 = tobd(tmp2);
  if (scale1 > scale2) {
    *bd2 = bd_bin_mul(tobd(tmp2), ten_pow(scale1 - scale2));
  } else if (scale1 < scale2) {
    *bd1 = bd_bin_mul(tobd(tmp1), ten_pow(scale2 - scale1));
  }
}

int get_exp(char *str) {
  int result = 0;
  char *ptr = str;
  for (; *ptr && *ptr != 'E'; ptr++);
  if (*ptr == 'E') result = strtol(ptr + 1, NULL, 10);
  return result;
}

s21_decimal float_string_to_decimal(char *str) {
  s21_decimal result = Decimal(0);
  int digits = 6;
  char *ptr = str;
  int exp = get_exp(str) - 6;
  for (; *ptr && ((*ptr >= '0' && *ptr <= '9') || *ptr == '.'); ptr++) {
    if (*ptr == '.') continue;
    s21_decimal tmp = Decimal(0);
    s21_mul(Decimal(*ptr - '0'), ten_pow(digits), &tmp);
    s21_add(result, tmp, &result);
    digits--;
  }
  if (exp > 0) {
    s21_mul(result, ten_pow(exp), &result);
  } else if (exp < 0) {
    if (exp < -28) {
      s21_div(result, ten_pow(28), &result);
      exp += 28;
    }
    s21_div(result, ten_pow(-exp), &result);
  }
  return result;
}

void clear(s21_decimal *decimal) {
  decimal->bits[0] = 0;
  decimal->bits[1] = 0;
  decimal->bits[2] = 0;
  decimal->bits[3] = 0;
}

void clear_service(s21_decimal *value) { value->bits[3] = 0; }

s21_decimal Decimal(int number) {
  s21_decimal result;
  clear(&result);
  result.bits[0] = number;
  return result;
}

s21_decimal ten_pow(int pow) { return ten_pows[pow]; }

s21_decimal zerofive(void) {
  s21_decimal result = {{0x5, 0x0, 0x0, 0x10000}};
  return result;
}

s21_decimal min_decimal(void) {
  s21_decimal result = {{0x1, 0x0, 0x0, 0x1C0000}};
  return result;
}

s21_decimal max_decimal(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  return result;
}

s21_decimal max_int(void) {
  s21_decimal result = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};

  return result;
}

s21_decimal min_int(void) {
  s21_decimal result = {{0x80000000, 0x0, 0x0, 0x80000000}};

  return result;
}

big_decimal tobd(s21_decimal value) {
  big_decimal result;
  result.decimals[0] = value;
  result.decimals[1] = Decimal(0);
  return result;
}

s21_decimal inf(void) {
  s21_decimal result = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF}};
  return result;
}

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

s21_decimal s21_remove_trailing_zeros(s21_decimal value) {
  s21_decimal result = value;
  int scale = get_scale(value);
  int sign = get_sign(value);
  if (scale > 0 && is_correct(value)) {
    big_decimal remainder = tobd(Decimal(0));
    big_decimal tmp = tobd(value);
    clear_service(&tmp.decimals[0]);
    clear_service(&tmp.decimals[1]);
    while (scale > 0 && bd_is_null(remainder)) {
      tmp = bd_bin_div(tmp, tobd(ten_pow(1)), &remainder);
      if (bd_is_null(remainder)) {
        scale--;
        result = tmp.decimals[0];
      }
    }
    set_scale(&result, scale);
    set_sign(&result, sign);
  }

  return result;
}

s21_decimal s21_round_banking(s21_decimal integral, s21_decimal fractional) {
  s21_decimal half = zerofive();
  s21_decimal result;
  if (s21_is_equal(fractional, half)) {
    if (is_even(integral)) {
      result = integral;
    } else {
      result = bin_add(integral, Decimal(1));
    }
  } else if (s21_is_greater(fractional, half)) {
    result = bin_add(integral, Decimal(1));
  } else {
    result = integral;
  }
  return result;
}
