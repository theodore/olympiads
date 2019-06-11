#include <iostream>

using namespace std;

struct a{
	static int n;
	int m;
	 a(int);
	void output();
};
int a::n = 9;

a::a(int s){
	m = s;
}

void a::output(){
	cout << m << endl;
}

int main(){
	a s(5);
	s.output();
	s.n = 4;
	cout << s.n << endl;
	return 0;
}
