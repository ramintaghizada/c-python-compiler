int main() {
  int a = -21, b = 11;
  int c = 184;
  int d = 8;
  b -= b;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c |= ((d < (-b)) * (b < 79));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d &= (a < ((b * 35) * (46 >= 69)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d = (((c + 94) < (74 * 5)) | ((57 | b) ^ (30 << (38 & 15))));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c = ((~(75 % ((b & 7) + 1))) == 3);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c |= (((10 << (c & 15)) == (~d)) < ((95 | 36) * (d || d)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c &= (((a == b) > 6) / (((c && (d == a)) & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b |= (((-a) <= (33 - c)) + ((44 < a) ? (b == b) : (91 << (44 & 15))));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
