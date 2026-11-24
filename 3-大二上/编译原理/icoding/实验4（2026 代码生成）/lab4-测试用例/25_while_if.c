int get_one(int a) {
  return 1;
}

int deepWhileBr(int a, int b) {
  int c;
  c = a + b;
  while (c < 75) {
    int d;
    d = 42;
    if (c < 100) {
      c = c + d;
      if (c > 99) {
        int e;
        e = d * 2;
        if (get_one(0) == 1) {
          c = e * 2;
        }
      }
    }
  }
  return (c);
}

int main() {
  int p;
  p = 2;
  p = deepWhileBr(p, p);
  putint(p);
  return 0;
}