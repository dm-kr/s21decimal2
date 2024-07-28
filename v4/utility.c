#include "s21_decimal.h"

bd tobd(s21_decimal value) {
  bd dec;
  for (int i = 0; i < BDSIZE; i++) {
    if (i < 3) {
      dec.bits[i] = value.bits[i];
    } else {
      dec.bits[i] = 0;
    }
  }
  dec.scale = scale(value);
  dec.sign = sign(value);
  dec.overflow = 0;
  return dec;
}

s21_decimal tos21(bd value) {
  bd temp = value;
  int sc = value.scale;
  // printf("\n\n %d \n\n", get_significants(temp));
  while (get_significants(temp) > 96) {
    temp = downscale(temp, 1);
    sc--;
  }
  s21_decimal res = Decimal(0);
  for (int i = 0; i < 3; i++) {
    res.bits[i] = temp.bits[i];
  }
  s_scale(&res, sc);
  return res;
}

void pbd(bd value) {
  printf("Scale: %d\n", value.scale);
  if (value.sign == 1) {
    printf(" - ");
  } else {
    printf(" + ");
  }

  for (int i = BDBITS - 1; i >= 0; i--) {
    if (i % 32 == 0 && i > 0) printf(" ");
    printf("%d", get(value, i));
  }
  printf("\n");
}

int get(bd value, int bit) {
  return (value.bits[bit / 32] & (1 << bit % 32)) != 0;
}

void set(bd* value, int bit, int val) {
  if (val == 0) {
    value->bits[bit / 32] &= ~(1 << bit % 32);
  } else {
    value->bits[bit / 32] |= (1 << bit % 32);
  }
}

int _and(int a, int b) { return a & b; }
int _or(int a, int b) { return a | b; }
int _xor(int a, int b) { return a ^ b; }

bd logic(bd value_1, bd value_2, Operation op) {
  bd result = tobd(Decimal(0));
  for (int i = 0; i < BDBITS; i++) {
    int a = get(value_1, i);
    int b = get(value_2, i);
    set(&result, i, op(a, b));
  }
  return result;
}

bd shift(bd value, int dir, int n) {
  bd shifted = value;
  int carry = 0;
  int temp = 0;
  for (int count = 0; count < n; count++) {
    carry = 0;
    for (int i = 0; i < BDBITS; i++) {
      int j = !dir ? (BDBITS - 1) - i : i;
      temp = get(shifted, j);
      set(&shifted, j, carry);
      carry = temp;
    }
  }
  shifted.overflow = (carry * dir) != 0;
  return shifted;
}

int is_null(bd value) {
  int ret = 1;
  for (int i = 0; i < BDSIZE; i++) {
    if (value.bits[i] != 0) ret = 0;
  }
  return ret;
}

bd add(bd v1, bd v2) {
  bd res = tobd(Decimal(0));
  bd a = v1;
  bd b = v2;
  bd carry = tobd(Decimal(0));
  while (!is_null(b)) {
    carry = logic(a, b, _and);
    a = logic(a, b, _xor);
    b = shift(carry, LEFT, 1);
  }
  res = a;
  return res;
}

bd invert(bd value) {
  bd inverted = tobd(Decimal(0));
  for (int i = 0; i < BDBITS; i++) {
    set(&inverted, i, 1 - get(value, i));
  }
  return inverted;
}

bd to_acode(bd value) {
  bd temp = invert(value);
  temp.sign = 0;
  temp.scale = 0;
  bd one = tobd(Decimal(1));
  temp = add(temp, one);
  return temp;
}

bd sub(bd v1, bd v2) {
  bd b = to_acode(v2);
  bd res = add(v1, b);
  return res;
}

void normalize(bd* v1, bd* v2) {
  int as = v1->scale;
  int bs = v2->scale;
  if (as > bs) {
    *v2 = upscale(*v2, as - bs);
  } else if (bs > as) {
    *v1 = upscale(*v1, bs - as);
  }
}

int isg(bd v1, bd v2) {
  int ret = 0;
  int end = 0;
  bd a = v1;
  bd b = v2;
  normalize(&a, &b);
  for (int i = BDBITS - 1; i >= 0 && end == 0; i--) {
    if (get(a, i) != get(b, i)) {
      if (get(a, i) > get(b, i)) {
        ret = 1;
      }
      end = 1;
    }
  }
  return ret;
}

int ise(bd v1, bd v2) {
  int ret = 1;
  bd a = v1;
  bd b = v2;
  normalize(&a, &b);
  for (int i = BDBITS - 1; i >= 0; i--) {
    if (get(a, i) != get(b, i)) {
      ret = 0;
    }
  }
  return ret;
}

int isgore(bd v1, bd v2) { return (isg(v1, v2) || ise(v1, v2)); }

bd upscale(bd value, int n) {
  bd res = value;
  res.scale = 0;
  res.sign = 0;
  for (int i = 0; i < n; i++) {
    res = add(shift(res, LEFT, 1), shift(res, LEFT, 3));
  }
  return res;
}

int get_significants(bd value) {
  int i = BDBITS - 1;
  // pbd(value);
  for (; i >= 0 && get(value, i) == 0; i--);
  return i + 1;
}

bd _div(bd v1, bd v2) {
  bd res = tobd(Decimal(0));
  bd a = v1;
  bd b = v2;
  int asc = a.scale;
  while (!isgore(a, b)) {
    a = upscale(a, 1);
    asc++;
  }
  int sa = get_significants(a);
  int sb = get_significants(b);
  b = shift(b, LEFT, sa - sb);
  while (!is_null(b) && get_significants(b) >= sb) {
    res = shift(res, LEFT, 1);
    if (isgore(a, b)) {
      a = sub(a, b);
      set(&res, 0, 1);
    }
    b = shift(b, RIGHT, 1);
  }

  return res;
}

bd get10(int p) {
  bd value = tobd(Decimal(1));
  for (int i = 0; i < p; i++) {
    value = upscale(value, 1);
  }
  return value;
}

bd downscale(bd value, int n) {
  bd res = value;
  res.scale = 0;
  res.sign = 0;
  bd divider = get10(n);
  for (int i = 0; i < n; i++) {
    res = _div(res, divider);
  }
  return res;
}

int is_correct(s21_decimal val) {
  int ret = scale(val) < 29 && scale(val) > -1;
  for (int i = 0; i < 32; i++) {
    if (bit(val, i + 96) == 1) {
      if ((i < 16) || (i > 23 && i < 31)) ret = 0;
    }
  }
  return ret;
}

int error(s21_decimal v1, s21_decimal v2) {
  return !is_correct(v1) || !is_correct(v2);
}

int resign(s21_decimal value1, s21_decimal value2) {
  int s = 0;
  int asign = sign(value1);
  int bsign = sign(value2);
  s21_decimal a = value1;
  s21_decimal b = value2;
  s_sign(&a, 0);
  s_sign(&b, 0);
  if (asign == bsign) {
    s = asign;
  } else if (s21_is_greater(a, b)) {
    s = asign;
  } else {
    s = bsign;
  }
  if (is_null(tobd(value1)) && is_null(tobd(value2))) s = 0;
  return s;
}

int check_overflow(bd value) {
  int ret = 0;
  bd temp = value;
  int sc = value.scale;
  // pbd(temp);
  while (get_significants(temp) > 96 && sc > 0) {
    temp = downscale(temp, value.scale);
    sc--;
  }
  if (get_significants(temp) > 96) {
    ret = 1;
  }
  return ret;
}