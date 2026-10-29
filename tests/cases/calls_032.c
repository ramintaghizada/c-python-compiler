int g = 26;
int wide(int p0, int p1, int p2, int p3, int p4) { return p0 * 1 + p1 * 2 + p2 * 3 + p3 * 4 + p4 * 5 + g; }
int twice(int x) { return wide(x + 0, x + 1, x + 2, x + 3, x + 4) - x; }
int ack(int m, int n) { if (m == 0) return n + 1; if (n == 0) return ack(m - 1, 1); return ack(m - 1, ack(m, n - 1)); }
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }
int main() {
  int r = wide(55, 16, 27, 64, 90);
  g++;
  printf("%d %d %d\n", r, twice(5), g);
  printf("%d %d %s\n", ack(2, 3), fact(1), "str\tok");
  return (wide(0, 73, 22, 45, -7) + ack(1, 3)) & 255;
}
