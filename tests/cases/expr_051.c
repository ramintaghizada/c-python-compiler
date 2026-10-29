int main() {
  int a = 32, b = -20;
  int c = 183;
  int d = 3;
  a += (28 ? ((a || c) & (a == c)) : ((34 <= a) * (b >> (c & 15))));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d ^= (((47 + b) || a) + (-(81 == b)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b += (((61 && a) && (25 != b)) >= ((d << (d & 15)) + (d != c)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a = (b + (7 >> ((88 >> (b & 15)) & 15)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
