int main() {
  int a = -42, b = 17;
  int c = 946;
  int d = 2;
  b &= (((a < 64) && c) >= (-(!a)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a *= ((b < d) != (96 | (d >= 70)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = (((15 * b) >> (39 & 15)) * (a || (69 + d)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b |= ((a > (5 << (38 & 15))) >= ((!c) > a));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b &= (((c < c) <= (c - d)) == (33 & (c <= 23)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d &= b;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
