/*
PROB: charrec
LANG: C++
*/
// There is a bug, didn't concern about '?'
#pragma warning(disable: 4996)
#include <iostream>
#include <cstring>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define MIN(a, b, c) min(a, min(b, c))
#define inf 1<<30
#define lim 120
#define Debug
#define HOME
#define F(x) ((x)?((x)==1?20:21):19)
#define D(x) MIN(row[x].dif[0], row[x].dif[1], row[x].dif[2])

using namespace std;

char font[27][20][21], text[1200][21];
int n;
struct R{
	int ans[3], dif[3]; // 0 - 19, 1 - 20, 2 - 21
} row[1200];

/*
class queue{
	bool in[1200];
	int num;
public:
	inline bool empty();
	inline int pop();
	inline void push(int);
} q;
bool queue::empty(){
	return !num;
}
int queue::pop(){
	--num;
	for (int i=n-1; i>=0; --i)
		if (in[i]){
			in[i] = false;
			return i;
		}
	return -1;
}
void queue::push(int x){
	num += in[x] ^ 1;
	in[x] = true;
}
*/

void calc(){
	memset(row, 11, sizeof row);
#define R(x) row[n-1].dif[x]
	R(0) = R(1) = R(2) = 0;
#undef R
	//while (!q.empty()){
	for (int cur=n-1; cur>=18; --cur){
		// 20 rows
		if (cur >= 19)
			for (int i=0; i<27; ++i){
				int now(0);
				for (int j=0; j<20; ++j)
					for (int k=0; k<20; ++k)
						if (font[i][j][k] != text[cur-19+j][k])
							++now;
				if (now+D(cur) < row[cur-19].dif[1]){
					row[cur-19].dif[1] = now + D(cur);
					row[cur-19].ans[1] = i;
					q.push(cur-19);
				}
			}
		// 21 rows
		if (cur >= 20)
			for (int i=0; i<27; ++i)
				for (int line=0; line<20; ++line){
					int now(0);
					for (int j=0; j<line; ++j)
						for (int k=0; k<20; ++k)
							if (font[i][j][k] != text[cur-20+j][k])
								++now;
					int u(0), v(0);
					for (int k=0; k<20; ++k){
						if (font[i][line][k] != text[cur-20+line][k])
							++u;
						if (font[i][line][k] != text[cur-19+line][k])
							++v;
					}
					now += min(u, v);
					for (int j=line+1; j<20; ++j)
						for (int k=0; k<20; ++k)
							if (font[i][j][k] != text[cur-19+j][k])
								++now;
					if (now+D(cur) < row[cur-20].dif[2]){
						row[cur-20].dif[2] = now + D(cur);
						row[cur-20].ans[2] = i;
						q.push(cur-20);
					}
				}
		// 19 rows
		if (cur >= 18)
			for (int i=0; i<27; ++i)
				for (int line=0; line<20; ++line){
					int now(0);
					for (int j=0; j<line; ++j){
						for (int k=0; k<20; ++k)
							if (font[i][j][k] != text[cur-18+j][k])
								++now;
					}
					for (int j=line+1; j<20; ++j)
						for (int k=0; k<20; ++k)
							if (font[i][j][k] != text[cur-19+j][k])
								++now;
					if (now+D(cur) < row[cur-18].dif[0]){
						row[cur-18].dif[0] = now + D(cur);
						row[cur-18].ans[0] = i;
						q.push(cur-18);
					}
				}
	}
}

void output(){
	freopen("charrec.out", "w", stdout);
	for (int i=0, plus; i<n; i+=F(plus)){
		plus = 0;
		if (row[i].dif[1] < row[i].dif[plus])
			plus = 1;
		if (row[i].dif[2] < row[i].dif[plus])
			plus = 2;
#define x row[i].ans[plus]
		putchar(x?x+'a'-1:' ');
#undef x
	}
	putchar('\n');
}

int main(){
#ifndef HOME
	freopen("font.in", "r", stdin);
#else
	freopen("charrec_font.in", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i=0; i<=26; ++i)
		for (int j=0; j<20; ++j)
			scanf("%s", font[i][j]);

	freopen("charrec.in", "r", stdin);
	scanf("%d", &n);
	for (int i=0; i<n; ++i)
		scanf("%s", text[i]);

	calc();
	output();
	return 0;
}
