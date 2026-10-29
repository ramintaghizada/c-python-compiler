int main() {
  int a = -46, b = -16;
  int c = 712;
  int d = -3;
  a &= (~((97 <= 98) >> ((48 | c) & 15)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c += (((a + 28) == (c + b)) - ((d < c) % ((c & 7) + 1)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c ^= (a & ((a << (d & 15)) || (b * 96)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c = 37;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d |= (((d >= d) - (b == 32)) > (-89));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b -= (((82 & 8) % (((a == d) & 7) + 1)) * (84 / ((c & 7) + 1)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
