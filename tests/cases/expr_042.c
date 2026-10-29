int main() {
  int a = 34, b = -14;
  int c = 924;
  int d = 8;
  d &= (18 ? d : ((c | a) > (16 | d)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c |= ((!54) || c);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a += (74 * ((d & b) << (b & 15)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a &= (75 ? b : (!(31 * b)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b *= d;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c -= (((c ? 48 : b) > (8 == c)) % ((((!d) != (b | 74)) & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
