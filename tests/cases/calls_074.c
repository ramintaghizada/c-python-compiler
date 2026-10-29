int g = 7;
int wide(int p0, int p1) { return p0 * 1 + p1 * 2 + g; }
int twice(int x) { return wide(x + 0, x + 1) - x; }
int ack(int m, int n) { if (m == 0) return n + 1; if (n == 0) return ack(m - 1, 1); return ack(m - 1, ack(m, n - 1)); }
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }
int main() {
  int r = wide(20, 34);
  g++;
  printf("%d %d %d\n", r, twice(23), g);
  printf("%d %d %s\n", ack(2, 1), fact(7), "str\tok");
  return (wide(70, 74) + ack(1, 3)) & 255;
}
