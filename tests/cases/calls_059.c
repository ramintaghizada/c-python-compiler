int g = 17;
int wide(int p0) { return p0 * 1 + g; }
int twice(int x) { return wide(x + 0) - x; }
int ack(int m, int n) { if (m == 0) return n + 1; if (n == 0) return ack(m - 1, 1); return ack(m - 1, ack(m, n - 1)); }
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }
int main() {
  int r = wide(66);
  g++;
  printf("%d %d %d\n", r, twice(11), g);
  printf("%d %d %s\n", ack(2, 3), fact(8), "str\tok");
  return (wide(92) + ack(1, 3)) & 255;
}
