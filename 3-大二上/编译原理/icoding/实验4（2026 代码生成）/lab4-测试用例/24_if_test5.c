// test if-{if}-else
int if_if_Else() {
  int a;
  a = 5;
  int b;
  b = 10;
  if(a == 5){
    if (b == 10) 
      a = 25;
  }
    else 
      a = a + 15;
  return (a);
}

int main(){
  return (if_if_Else());
}
