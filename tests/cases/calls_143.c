int g = 43;
int wide(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7) { return p0 * 1 + p1 * 2 + p2 * 3 + p3 * 4 + p4 * 5 + p5 * 6 + p6 * 7 + p7 * 8 + g; }
int twice(int x) { return wide(x + 0, x + 1, x + 2, x + 3, x + 4, x + 5, x + 6, x + 7) - x; }
int ack(int m, int n) { if (m == 0) return n + 1; if (n == 0) return ack(m - 1, 1); return ack(m - 1, ack(m, n - 1)); }
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }
int main() {
  int r = wide(38, 87, 31, 33, 27, 62, 57, 30);
  g++;
  printf("%d %d %d\n", r, twice(23), g);
  printf("%d %d %s\n", ack(2, 1), fact(5), "str\tok");
  return (wide(21, 11, 6, -3, 35, 59, -1, 88) + ack(1, 3)) & 255;
}
