int main() {
  int a = -50, b = -9;
  int c = 414;
  int d = 2;
  c *= (-((82 == b) % (((b <= d) & 7) + 1)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d = 30;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d &= (((a / ((33 & 7) + 1)) + (a >> (d & 15))) != (82 || d));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a ^= (((~c) < (76 / ((b & 7) + 1))) - ((c << (13 & 15)) ^ (!a)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a = (d & ((10 || a) <= (b <= a)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a |= c;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
