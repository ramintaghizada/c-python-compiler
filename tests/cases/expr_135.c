int main() {
  int a = -26, b = 13;
  int c = 579;
  int d = 5;
  d -= ((49 > (d <= 6)) << (38 & 15));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = d;
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a += (~((a ? d : b) | (d << (b & 15))));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  b = (((-58) << (c & 15)) % ((a & 7) + 1));
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  a += (((38 / ((83 & 7) + 1)) || (49 ? 41 : 43)) == b);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  d += (((70 + a) || a) * d);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  c -= ((!(c ? b : 37)) || c);
  printf("%%d %%d %%d %%d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
