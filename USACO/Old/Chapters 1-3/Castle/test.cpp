#include <iostream>
using namespace std;
#pragma warning(disable:4996)

int main(){
	freopen("castle.in", "w", stdout);
	cout<<50<<' '<<50<<endl;
	for (int i=0; i<50; ++i){
		for (int j=0; j<50; ++j)
			cout<<15<<' ';
		cout<<endl;
	}
	return 0;
}
