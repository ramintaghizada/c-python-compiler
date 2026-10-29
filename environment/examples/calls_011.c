int g = 28;
int wide(int p0) { return p0 * 1 + g; }
int twice(int x) { return wide(x + 0) - x; }
int ack(int m, int n) { if (m == 0) return n + 1; if (n == 0) return ack(m - 1, 1); return ack(m - 1, ack(m, n - 1)); }
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }
int main() {
  int r = wide(62);
  g++;
  printf("%d %d %d\n", r, twice(32), g);
  printf("%d %d %s\n", ack(2, 0), fact(3), "str\tok");
  return (wide(73) + ack(1, 3)) & 255;
}
