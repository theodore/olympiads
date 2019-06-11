/*
PROB:buylow
LANG:C++
*/
#include <iostream>

using namespace std;

class INT{
	static const int base = 100000000;
	int bit;
	int num[10];

	INT operator+(INT);
 public:
	INT operator=(int);
	INT operator+=(INT);
	void output();
};

//static const int base = 100000000;

INT INT::operator+(INT x){
	bit = max(bit, x.bit);
	int more = 0;
	for (int i=0; i<bit; ++i){
		num[i] += x.num[i] + more;
		more = num[i] / base;
		num[i] %= base;
	}
	if (more)
		num[bit++] = more;
	return *this;
}

INT INT::operator=(int x){
	bit = 1;
	num[0] = x;
	return *this;
}

INT INT::operator+=(INT x){
	return *this = *this + x;
}

void INT::output(){
	for (int i=bit-1; i>=0; --i)
		printf("%d", num[i]);
}

int n;
struct{
	int v, size;
	INT c;
} s[5011];

int list[5011];
int num;

int main(){
	freopen("buylow.in", "r", stdin);
	freopen("buylow.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<=n; ++i){
		if (i==n)
			s[i].v = 0;
		else
			scanf("%d", &s[i].v);
		s[i].size = 0;
		num = 0;
		for (int j=i-1; j>=0; --j)
			if (s[j].v > s[i].v){
				if (s[j].size == s[i].size){
					bool already = false;
					for (int i=0; i<num; ++i)
						if (s[list[i]].v == s[j].v){
							already = true;
							break;
						}
					if (!already)
						list[num++] = j;
				}
				else if (s[j].size > s[i].size){
					s[i].size = s[j].size;
					num = 1;
					list[0] = j;
				}
			}
		++s[i].size;
		s[i].c = s[i].size==1 ? 1 : 0;
		for (int j=0; j<num; ++j)
			s[i].c += s[list[j]].c;
		//debug
//		if (i == 12){
//			printf("List\n\t");
//		for (int i=0; i<num; ++i)
//			printf("%d ", list[i]);
//		printf("\n");
//		}
	}
//	for (int i=0; i<n; ++i)
//		printf("%d %d\n", s[i].size, s[i].c);

//	int best = n-1;
//	for (int i=n-1; i>=0; --i)
//		if (s[i].size > s[best].size)
//			best = i;
//	printf("%d %d\n", s[best].size, s[best].c);
	printf("%d ", s[n].size-1);
	s[n].c.output();
	putchar('\n');
	return 0;
}
