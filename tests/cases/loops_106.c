int gcd(int a, int b) { while (b) { int t = a % b; a = b; b = t; } return a; }
int collatz(int n) { int steps = 0; while (n != 1) { if (n % 2 == 0) n = n / 2; else n = 3 * n + 1; steps++; } return steps; }
int digsum(int n) { int s = 0; do { s += n % 10; n /= 10; } while (n > 0); return s; }
int main() {
  int total = 0, i, j;
  for (i = 1; i <= 31; i++) {
    for (j = 1; j <= 9; j++) { if (j > i) break; if ((i + j) % 3 == 0) continue; total += gcd(i * 7, j * 3 + 1); }
    total += collatz(i) + digsum(i * 10);
    if (total > 100000) break;
  }
  printf("total=%d\n", total);
  for (int x = 0; x < 31; x++) putchar('a' + x % 26);
  putchar('\n');
  return total % 200;
}
