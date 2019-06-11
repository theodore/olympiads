/*
ID:theodor8
PROB:pprime
LANG:C++
*/
#include <iostream>
#include <cmath>
using namespace std;
#pragma warning(disable:4996)

inline bool is_prime(const int& x){
	for (int i=2; i*i<=x; ++i)
		if (x % i == 0)
			return false;
	return true;
}
inline void search(const int& a, const int& b){
	int l = log10(double(a))+1, r = log10(double(b))+1;
	switch(l){
	case 1:
		for (int i=2; i<=7; ++i){
			if (i > b)
				break;
			if (i >= a && (i == 2 || i == 3 || i == 5 || i == 7))
				printf("%d\n", i);
		}
		if (r == 1)
			break;
	case 2:
		for (int i=1; i<10; ++i){
			int x = i*10+i;
			if (x > b)
				break;
			if (x >= a && is_prime(x))
				printf("%d\n", x);
		}
		if (r == 2)
			break;
	case 3:
		for (int i=1; i<10; ++i)
			for (int j=0; j<10; ++j){
				int x = i*100 + j*10 + i;
				if (x > b)
					goto out_3;
				if (x >= a && is_prime(x))
					printf("%d\n", x);
			}
out_3:
		if (r == 3)
			break;
	case 4:
		for (int i=1; i<10; ++i)
			for (int j=0; j<10; ++j){
				int x = i*1000 + j*100 + j*10 + i;
				if (x > b)
					goto out_4;
				if (x >= a && is_prime(x))
					printf("%d\n", x);
			}
out_4:
		if (r == 4)
			break;
	case 5:
		for (int i=1; i<10; ++i)
			for (int j=0; j<10; ++j)
				for (int I=0; I<10; ++I){
					int x = i*10000 + j*1000 + I*100 + j *10 + i;
					if (x > b)
						goto out_5;
					if (x >= a && is_prime(x))
						printf("%d\n", x);
				}
out_5:
		if (r == 5)
			break;
	case 6:
for (int i1=1; i1<10; ++i1)
for (int i2=0; i2<10; ++i2)
for (int i3=0; i3<10; ++i3){
	int x = i1*100000 + i2*10000 + i3*1000 + i3*100 + i2*10 + i1;
	if (x > b)
		goto out_6;
	if (x >= a && is_prime(x))
		printf("%d\n", x);
}
out_6:
	if (r == 6)
		break;
	case 7:
for (int i1=1; i1<10; ++i1)
for (int i2=0; i2<10; ++i2)
for (int i3=0; i3<10; ++i3)
for (int i4=0; i4<10; ++i4){
	int x=i1*1000000 + i2*100000 + i3*10000 + i4*1000 + i3*100 + i2*10 + i1;
	if (x > b)
		goto out_7;
	if (x >= a && is_prime(x))
		printf("%d\n", x);
}
out_7:
	if (r == 7)
		break;
	case 8:
for (int i1=1; i1<10; ++i1)
for (int i2=0; i2<10; ++i2)
for (int i3=0; i3<10; ++i3)
for (int i4=0; i4<10; ++i4){
	int x=i1*10000000 + i2*1000000 + i3*100000 + i4*10000 + i4*1000 + i3*100 + i2*10 + i1;
	if (x > b)
		goto out_8;
	if (x >= a && is_prime(x))
		printf("%d\n", x);
}
out_8:
	if (r == 8)
		break;
	case 9:
for (int i1=1; i1<10; ++i1)
for (int i2=0; i2<10; ++i2)
for (int i3=0; i3<10; ++i3)
for (int i4=0; i4<10; ++i4)
for (int i5=0; i5<10; ++i5){
	int x=i1*100000000 + i2*10000000 + i3*1000000 + i4*100000 + i5*10000 + i4*1000 + i3*100 + i2*10 + i1;
	if (x > b)
		goto out_9;
	if (x >= a && is_prime(x))
		printf("%d\n", x);
}
out_9:
	if (r == 9)
		break;
	}
}
int main(){
	freopen("pprime.in", "r", stdin);
	freopen("pprime.out", "w", stdout);
	int l, r;
	scanf("%d%d", &l, &r);
	search(l, r);
	return 0;
}
