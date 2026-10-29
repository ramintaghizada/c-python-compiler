int main() {
  int a = 50, b = 36;
  int c = 82;
  int d = 9;
  d &= 40;
  printf("%d %d %d %d\n", a, b, c, d);
  a -= 6;
  printf("%d %d %d %d\n", a, b, c, d);
  c |= (((!9) * (b & 42)) ^ (!(c == d)));
  printf("%d %d %d %d\n", a, b, c, d);
  d *= (((a | b) ^ (26 % ((c & 7) + 1))) && ((a >= 4) <= (72 << (a & 15))));
  printf("%d %d %d %d\n", a, b, c, d);
  c &= 59;
  printf("%d %d %d %d\n", a, b, c, d);
  a = (((32 || 12) >> ((d && a) & 15)) <= (d ? d : (98 ? a : a)));
  printf("%d %d %d %d\n", a, b, c, d);
  d &= (~(b - (a != c)));
  printf("%d %d %d %d\n", a, b, c, d);
  a |= (((21 < 73) + (13 < b)) - ((17 != 35) % (((43 <= 33) & 7) + 1)));
  printf("%d %d %d %d\n", a, b, c, d);
  return (a ^ b ^ c ^ d) & 127;
}
