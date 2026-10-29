int main() {
  int a = -17, b = -18;
  int c = 920;
  int d = 8;
  b = (-((56 != b) > (c != d)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b ^= a;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c -= (((~c) != 37) >> ((!(74 ^ 59)) & 15));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a -= c;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c ^= (((b || 75) & (d < 26)) != ((29 >= c) & a));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a += ((58 ^ (13 || d)) << (((b || 79) ? (c && d) : (43 << (77 & 15))) & 15));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
