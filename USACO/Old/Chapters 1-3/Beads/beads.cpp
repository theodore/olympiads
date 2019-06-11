/*
ID:theodor8
PROB:beads
LANG:C++
*/
#include <iostream>
#include <string>
using namespace std;

int n;
string necklace;
bool change[800], corrected = false;

int main(){
	freopen("beads.in", "r", stdin);
	freopen("beads.out", "w", stdout);
	scanf("%d", &n);
	cin>>necklace;
	necklace += necklace;
	int ans = 0;
	char color = 'w';
	for (int i = 0, j = 0, colors = 1; j < 2*n; ++j){
		if (!(color == 'w' || necklace[j] == 'w' || necklace[j] == color)){
			change[j] = true;
			if (colors == 2){
				++i;
				while (!change[i])
					++i;
				if (corrected){
					++i;
					while (!change[i])
						++i;
					corrected = false;
				}
				for (int x = i - 1; x >=0; --x)
					if (necklace[x] == 'w') i = x, corrected = true;
					else break;
			}
			else colors = 2;
		}
		color = necklace[j] == 'w'?color:necklace[j];
		ans = max(ans, j-i+1);
		//printf("%d,%d,%d,%d,%c\n", i, j, ans, colors, color);
	}
	if (ans > n) ans = n;
	printf("%d\n", ans);
	return 0;
}