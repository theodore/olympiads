/*
PROB:msquare
LANG:C++
*/
#include <iostream>
#pragma warning(disable:4996)
//#define Debug

using namespace std;

typedef int state[9];

struct store{
	int value, step;
	int b4, dir;
#ifdef Debug
	operator int(){
		return value;
	}
#endif
};

struct queue{
	int head, tail;
	store ele[40200];
	 queue();
	store pop();
	void push(store);
	bool empty();
} q;
queue::queue(){
	head = tail = 0;
}
store queue::pop(){
	return ele[head++];
}
void queue::push(store x){
	ele[tail++] = x;
}
bool queue::empty(){
	return head == tail;
}

inline int fact(int x){
	int ret = 1;
	for (int i=1; i<=x; ++i)
		ret *= i;
	return ret;
}

int encode(const state x){
	int code = 0, count[8];
	for (int i=0; i<8; ++i){
		if (x[i] == 8)
			continue;
		int& c = count[x[i]] = 0;
		for (int j=0; j<i; ++j)
			if (x[j] > x[i])
				++c;
	}
	for (int i=1; i<8; ++i)
		code += count[i] * fact(8-i);
	return code;
}

void decode(int code, state ret){
	int count[8];
	for (int i=1; i<8; ++i){
		count[i] = code / fact(8-i);
		code %= fact(8-i);
	}
	bool chosen[8] = {false};
	for (int i=1; i<8; ++i){
		int lim = count[i];
		for (int j=0, c=0; c<=lim; ++j)
			if (!chosen[j])
				if (c++ == lim){
					chosen[j] = true;
					ret[j] = i;
				}
	}
	for (int i=0; i<8; ++i)
		if (!chosen[i])
			ret[i] = 8;
}

int trans(const int code, int dir){
	state orig, ret;
	decode(code, orig);
	switch(dir){
	case 0:
		for (int i=0; i<4; ++i){
			ret[i] = orig[7-i];
			ret[7-i] = orig[i];
		}
		break;
	case 1:
		ret[0] = orig[3];
		ret[7] = orig[4];
		for (int i=1; i<4; ++i){
			ret[i] = orig[i-1];
			ret[7-i] = orig[8-i];
		}
		break;
	case 2:
		ret[0] = orig[0];
		ret[1] = orig[6];
		ret[2] = orig[1];
		ret[3] = orig[3];
		ret[4] = orig[4];
		ret[5] = orig[2];
		ret[6] = orig[5];
		ret[7] = orig[7];
		break;
	}
	return encode(ret);
}

void print(int pos){
	if (q.ele[pos].b4)
		print(q.ele[pos].b4);
	putchar('A'+q.ele[pos].dir);
}
void output(int f, int dir){
	printf("%d\n", q.ele[f].step + 1);
	print(f);
	printf("%c\n", 'A'+dir);
}

bool my_hash[40320];
#ifdef Debug
void output(store x){
	state s;
	decode(x, s);
	for (int i=0; i<8; ++i)
		printf("%d", s[i]);
	printf("\t%d\n", x.step);
}
#endif
int main(){
	freopen("msquare.in", "r", stdin);
	freopen("msquare.out", "w", stdout);
	state temp;
	for (int i=0; i<8; ++i)
		scanf("%d", &temp[i]);
	int goal = encode(temp);
	for (int i=0; i<8; ++i)
		temp[i] = i+1;
	store a;
	if ((a.value = encode(temp)) == goal){
		printf("0\n\n");
		return 0;
	}
	a.step = 0;
	a.b4 = -1;
	q.push(a);
	my_hash[a.value] = true;
	while (!q.empty()){
		store s = q.pop();
#ifdef Debug
		output(s);
#endif
		for (int i=0; i<3; ++i){
			int t = trans(s.value, i);
			if (my_hash[t])
				continue;
			if (t == goal){
				output(q.head - 1, i);
				return 0;
			}
			else{
				store o;
				o.value = t;
				o.step = s.step + 1;
				o.b4 = q.head - 1;
				o.dir = i;
				q.push(o);
				my_hash[t] = true;
			}
		}
	}
	return 0;
}
