int main() {
  int a = -37, b = -48;
  int c = 792;
  int d = -4;
  d &= 75;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = (((d <= b) || b) / (((-(24 >> (d & 15))) & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b ^= (((d + 95) >= a) & ((c == a) - (b > a)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c ^= (((34 ? 57 : 69) & (b > 19)) + ((!25) & d));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a = (b ^ ((a % ((d & 7) + 1)) >= (a + c)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
