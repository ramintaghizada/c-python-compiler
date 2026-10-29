int main() {
  int a = -4, b = -24;
  int c = 528;
  int d = 4;
  b *= b;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d &= (18 >= (a - (a | 18)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d ^= (((35 >= c) << ((b << (11 & 15)) & 15)) & ((a | 35) != (50 ^ d)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d *= c;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d &= 20;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
