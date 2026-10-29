int main() {
  int a = -44, b = 25;
  int c = 37;
  int d = -9;
  c &= a;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a = (((57 ? d : 74) && (86 % ((b & 7) + 1))) - ((b >= c) != (91 == 52)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a = 33;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c &= (a - ((64 * 47) + c));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a &= (((b / ((d & 7) + 1)) + (c >> (21 & 15))) % ((9 & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = (((59 ? b : 21) % ((a & 7) + 1)) ? (!(c * d)) : (31 ^ (~c)));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
