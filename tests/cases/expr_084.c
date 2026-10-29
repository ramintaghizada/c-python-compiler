int main() {
  int a = -39, b = 0;
  int c = 962;
  int d = -2;
  c |= ((a == (c - d)) != ((67 >= 18) ^ (d + 68)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d = (3 - ((35 || 8) > (c <= 81)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c += (~a);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c ^= (((d >= 2) && (a + d)) & ((a * 18) - (b - c)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a = (~46);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c *= (((~b) != (59 + c)) << (((b / ((b & 7) + 1)) ? (c / ((c & 7) + 1)) : (a ? c : b)) & 15));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a = ((a && (98 + b)) && ((48 >= 2) && (a - a)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
