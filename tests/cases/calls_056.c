int g = 10;
int wide(int p0, int p1, int p2) { return p0 * 1 + p1 * 2 + p2 * 3 + g; }
int twice(int x) { return wide(x + 0, x + 1, x + 2) - x; }
int ack(int m, int n) { if (m == 0) return n + 1; if (n == 0) return ack(m - 1, 1); return ack(m - 1, ack(m, n - 1)); }
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }
int main() {
  int r = wide(82, 77, 73);
  g++;
  printf("%d %d %d\n", r, twice(13), g);
  printf("%d %d %s\n", ack(2, 0), fact(7), "str\tok");
  return (wide(13, 58, 93) + ack(1, 3)) & 255;
}
