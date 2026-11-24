// test if-else-if
int ifElseIf() {
  int a;
  a = 5;
  int b;
  b = 10;
  if(a == 6 || b == 0xb) {
    return a;
  }
  else {
    if (b == 10 && a == 1)
      a = 25;
    else if (b == 10 && a == -5)
      a = a + 15;
    else
      a = -+a;
  }

  return a;
}

int main(){
  putint(ifElseIf());
  return 0;
}