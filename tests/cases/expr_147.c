int main() {
  int a = 20, b = -41;
  int c = 333;
  int d = -2;
  a = a;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a *= (((70 ? a : c) | 78) ? ((d || d) < c) : ((~b) && (b <= 20)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c ^= (c == ((~b) < (d >> (b & 15))));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a &= (((a <= c) != 1) / ((((c ^ 7) && (b || b)) & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = (-c);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = (-(d + (84 && 26)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b ^= (((79 ? 87 : 44) % (((b && 1) & 7) + 1)) == (c ^ (24 * 90)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
