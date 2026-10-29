int main() {
  int a = -11, b = -34;
  int c = 607;
  int d = -2;
  b += (((78 >= 23) << ((a >> (c & 15)) & 15)) && d);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a -= 54;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = a;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c = (d >> ((d == (0 & d)) & 15));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
