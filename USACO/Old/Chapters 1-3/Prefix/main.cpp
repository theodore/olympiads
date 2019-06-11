/*
ID:theodor8
PROB:prefix
LANG:C++
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#pragma warning(disable:4996)

char list[210][15], s[200010];
int list_num, ans[200010];
inline int poss(const int& pos){
	int best(-1);
	char tmp[15];
	for (int i=0; i<list_num; ++i){
		memcpy(tmp, s+pos,strlen(list[i]));
		tmp[strlen(list[i])] = '\0';
		if (!strcmp(tmp, list[i]) &&
			(best==-1 ||
				strlen(list[best])+ans[pos+strlen(list[best])] <
				strlen(list[i])+ans[pos+strlen(list[i])]
			))
			best = i;
	}
	if (best == -1)
		return 0;
	else
		return strlen(list[best]);
}
void calc(){
	for (int start=strlen(s)-1; start>=0; --start){
		int n(poss(start));
		ans[start] = n + ans[start+n];
	}
}
int main(){
	freopen("prefix.in", "r", stdin);
	freopen("prefix.out", "w", stdout);
	for (; ; ){
		scanf("%s", list[list_num]);
		if (!strcmp(list[list_num], "."))
			break;
		else
			++list_num;
	}
	scanf("%s", s);
	while (scanf("%s", s+strlen(s)) != EOF);
	//End input
	calc();

	printf("%d\n", ans[0]);
	return 0;
}
