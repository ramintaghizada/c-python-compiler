int main() {
  int a = 0, b = 38;
  int c = 945;
  int d = 0;
  a |= (c - ((d < 67) | (a * a)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d *= (((24 / ((b & 7) + 1)) - (c % ((b & 7) + 1))) == ((d % ((21 & 7) + 1)) != (b % ((21 & 7) + 1))));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c ^= c;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c &= (((a <= d) ? (45 % ((21 & 7) + 1)) : 69) << (((d >> (c & 15)) != (5 * a)) & 15));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b *= 9;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a ^= ((a % (((a && d) & 7) + 1)) ^ ((b && 88) + (3 & c)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
