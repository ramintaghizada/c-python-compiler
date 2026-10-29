int main() {
  int a = -43, b = 12;
  int c = 558;
  int d = 1;
  d = (((2 & b) | (c && 11)) + ((!c) % (((-a) & 7) + 1)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a ^= (27 / ((((52 >= b) % ((b & 7) + 1)) & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c ^= (((38 * d) % (((c & d) & 7) + 1)) < (-b));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b += (a && a);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b &= 76;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a &= ((~(92 < b)) <= (47 >> ((b < 96) & 15)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
