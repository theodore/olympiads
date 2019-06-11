/*
TASK:starry
LANG:C++
*/
#include <iostream>
#include <cstring>

using namespace std;

typedef int map[105][105];

int n, m;

map ans;

struct S{
	static int num;
	map me;
	int x, y, c;

	 S();
	 S(int, int, int); // x, y, c, remember memset
	bool operator==(S);
	void operator=(S);
} cluster[26];
int S::num = 0;

void fill(int, int, int&, int&); // flood fill
void fill(int, int, int); // fill the ans with a char

int main()
{
	freopen("starry.in", "r", stdin);
	freopen("starry.out", "w", stdout);
	scanf("%d%d", &m, &n);
	for (int i=0; i<n; ++i)
		scanf("%s", ans[i]);
	// input
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			if (ans[i][j] == '1'){
				S now(1, 1, 0);
				fill(i, j, now.x, now.y);
				for (int ip=0; ip<now.x; ++ip)
					for (int jp=0; jp<now.y; ++jp)
						if (ans[ip+i][jp+j] == '*'){
							now[i][j] = '*';
							++now.c;
						}
				bool match = false;
				int color;
				for (int c=0; c<S::num; ++c)
					if (now == cluster[c]){
						match = true;
						color = c;
						break;
					}
				if (!match){
					// add a new one
					cluster[S::num] = now;
					color = S::num++;
				}
				fill(i, j, color);
			}
	// output
	for (int i=0; i<n; ++i)
		printf("%s\n", ans[i]);
	return 0;
}
