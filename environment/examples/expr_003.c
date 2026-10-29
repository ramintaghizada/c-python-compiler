int main() {
  int a = 39, b = 45;
  int c = 878;
  int d = -8;
  d += ((31 && (7 << (54 & 15))) & ((10 << (b & 15)) == (~91)));
  printf("%d %d %d %d\n", a, b, c, d);
  a = ((d >> (a & 15)) == (!79));
  printf("%d %d %d %d\n", a, b, c, d);
  c = 80;
  printf("%d %d %d %d\n", a, b, c, d);
  b *= b;
  printf("%d %d %d %d\n", a, b, c, d);
  d = (a >> (25 & 15));
  printf("%d %d %d %d\n", a, b, c, d);
  c -= c;
  printf("%d %d %d %d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
