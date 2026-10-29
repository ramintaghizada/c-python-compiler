int main() {
  int a = 23, b = -1;
  int c = 739;
  int d = -1;
  d = (b % ((((d + b) * (-a)) & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d = (((75 && d) + 84) != ((35 >= b) && (d - d)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b -= ((!(52 / ((a & 7) + 1))) | ((c << (d & 15)) && (d || 5)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b ^= (((c >> (b & 15)) ^ (a ^ a)) | ((d * c) >= (d ^ 11)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a &= 33;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d = (-(b | a));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
