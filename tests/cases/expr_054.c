int main() {
  int a = -37, b = 25;
  int c = 645;
  int d = 7;
  c = 38;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a = (10 - a);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d ^= ((a % (((c >> (72 & 15)) & 7) + 1)) > (a == (d ^ b)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b &= (a < ((4 == b) && (-d)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c *= (((-60) << (70 & 15)) / ((55 & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a &= (((d << (52 & 15)) % (((a * 100) & 7) + 1)) % ((b & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
