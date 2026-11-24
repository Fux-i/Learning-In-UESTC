// test if-if-else
int ififElse() {
  int a;
  a = 5;
  int b;
  b = 10;
  if(a == 5)
    if (b == 10) 
      a = 25;
    else 
      a = a + 15;
    
  return (a);
}

int main(){
  return (ififElse());
}
