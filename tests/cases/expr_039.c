int main() {
  int a = -23, b = -37;
  int c = 221;
  int d = -8;
  d += ((b << ((c % ((c & 7) + 1)) & 15)) | ((29 < 93) ? (3 ^ c) : (-56)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c &= ((24 * (a > 23)) - ((2 || a) | (-a)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d += ((!(d ? d : d)) || ((14 || d) && (d <= c)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d &= (a && 36);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b ^= (((b != a) >> ((11 <= b) & 15)) ^ c);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d |= (((-19) || (86 << (a & 15))) ? ((43 >> (d & 15)) >> ((83 || d) & 15)) : ((97 != b) && b));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
