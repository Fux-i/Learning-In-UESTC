int a;
int func(int p){
	p = p - 1;
	return p;
}
int main(){
	int b;
	a = 10;
	b = func(a);
	return b;
}
