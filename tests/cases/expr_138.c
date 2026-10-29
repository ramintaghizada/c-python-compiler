int main() {
  int a = 32, b = -17;
  int c = 715;
  int d = 5;
  c |= (-((d * 75) - c));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b -= (b <= ((43 & c) % (((c | b) & 7) + 1)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b &= (((a || 67) == (70 >> (56 & 15))) == (13 / (((97 > b) & 7) + 1)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c ^= ((c * (c ? 40 : c)) || (21 != 43));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = (((a >= d) != (b == d)) != ((91 + 45) || d));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a -= (((!95) <= 62) ? ((31 != a) ? (-d) : (25 % ((d & 7) + 1))) : (d == (a || 57)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
