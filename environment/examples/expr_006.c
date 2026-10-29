int main() {
  int a = 40, b = 48;
  int c = 246;
  int d = 0;
  d -= ((77 != 63) ^ (c * (24 | 40)));
  printf("%d %d %d %d\n", a, b, c, d);
  c ^= b;
  printf("%d %d %d %d\n", a, b, c, d);
  a = (~64);
  printf("%d %d %d %d\n", a, b, c, d);
  d &= c;
  printf("%d %d %d %d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
