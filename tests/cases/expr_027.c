int main() {
  int a = -47, b = -47;
  int c = 419;
  int d = 6;
  c += (c >> (((~35) - (d << (56 & 15))) & 15));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c -= (((-a) || c) << (c & 15));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d *= ((-(a & a)) && (!(b + 25)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a = (((c && a) << (43 & 15)) | (c >= (~a)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c |= ((~28) <= c);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c -= (a && ((c & 38) && b));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
