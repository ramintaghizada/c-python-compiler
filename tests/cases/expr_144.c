int main() {
  int a = 41, b = 28;
  int c = 832;
  int d = 5;
  c -= (!((b < d) | (-a)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a -= (((33 + b) % (((19 > c) & 7) + 1)) != (!d));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c = (b > 60);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b += (((88 / ((71 & 7) + 1)) - (b >> (a & 15))) / ((((20 << (a & 15)) == (a << (c & 15))) & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c = ((d & (a != 87)) ^ 8);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d *= (!((c ^ 98) << ((c < 14) & 15)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
