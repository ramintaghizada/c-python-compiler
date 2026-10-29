int main() {
  int a = 0, b = 17;
  int c = 173;
  int d = 5;
  b = (((c > a) | (57 || 25)) <= (15 * (b >= d)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c += (((!a) | (b >> (70 & 15))) - (~50));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d = (!((95 << (b & 15)) ^ (b << (a & 15))));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d = ((-(~d)) == ((~82) + (40 / ((69 & 7) + 1))));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c &= (((a != b) || d) == (c - (b ^ b)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
