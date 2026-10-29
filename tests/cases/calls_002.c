int g = 40;
int wide(int p0, int p1, int p2, int p3, int p4, int p5) { return p0 * 1 + p1 * 2 + p2 * 3 + p3 * 4 + p4 * 5 + p5 * 6 + g; }
int twice(int x) { return wide(x + 0, x + 1, x + 2, x + 3, x + 4, x + 5) - x; }
int ack(int m, int n) { if (m == 0) return n + 1; if (n == 0) return ack(m - 1, 1); return ack(m - 1, ack(m, n - 1)); }
int fact(int n) { return n <= 1 ? 1 : n * fact(n - 1); }
int main() {
  int r = wide(49, -1, 65, 23, 0, 79);
  g++;
  printf("%d %d %d\n", r, twice(28), g);
  printf("%d %d %s\n", ack(2, 1), fact(2), "str\tok");
  return (wide(41, 15, 81, 49, 55, 21) + ack(1, 3)) & 255;
}
