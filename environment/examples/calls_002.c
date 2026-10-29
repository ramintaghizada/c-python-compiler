int g = 97;
int wide(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10) { return p0 * 1 + p1 * 2 + p2 * 3 + p3 * 4 + p4 * 5 + p5 * 6 + p6 * 7 + p7 * 8 + p8 * 9 + p9 * 10 + p10 * 11 + g; }
int twice(int x) { return wide(x + 0, x + 1, x + 2, x + 3, x + 4, x + 5, x + 6, x + 7, x + 8, x + 9, x + 10) - x; }
int ack(int m, int n) { if (m == 0) return n + 1; if (n == 0) return ack(m - 1, 1); return ack(m - 1, ack(m, n - 1)); }
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }
int main() {
  int r = wide(45, 11, -3, 41, 65, 93, 26, 46, 93, 70, 6);
  g++;
  printf("%d %d %d\n", r, twice(5), g);
  printf("%d %d %s\n", ack(2, 1), fact(12), "str\tok");
  return (wide(69, 78, 40, 91, 63, 61, 24, -2, 17, 85, 6) + ack(1, 3)) & 255;
}
