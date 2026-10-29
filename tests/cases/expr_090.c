int main() {
  int a = -31, b = 43;
  int c = 428;
  int d = 2;
  b *= (((b * c) << ((56 + 100) & 15)) < ((50 >> (b & 15)) ^ (d % ((d & 7) + 1))));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = (50 < ((a >> (a & 15)) + (3 & c)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c ^= ((a == (c * d)) == ((b || a) != d));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d &= (((b >> (d & 15)) & d) * a);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c -= ((c % (((d || d) & 7) + 1)) >> (((d / ((61 & 7) + 1)) && (b != c)) & 15));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d ^= (((c % ((a & 7) + 1)) | (a | c)) * ((23 != b) + (52 * c)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
