/*
ID:theodor8
TASK:barn1
LANG:C++
*/
#include <iostream>
using namespace std;

int m, s, c, Min, Max, stall[210], blank[210];
int cmp(const void* a, const void* b)
{
	return *(int*)b - *(int*)a;
}
int cmp_stall(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}
void init(){
	scanf("%d%d%d", &m, &s, &c);
	for (int i=0; i<c; ++i){
		scanf("%d", &stall[i]);
		if (i == 0)
			Min = Max = stall[i];
		if (stall[i] < Min)
			Min = stall[i];
		if (stall[i] > Max)
			Max = stall[i];
	}
	qsort(stall, c, sizeof(int), cmp_stall);
	for (int i=1; i<c; ++i)
		blank[i-1] = stall[i] - stall[i-1] - 1;
	qsort(blank, c-1, sizeof(int), cmp);
}
void calc()
{
	int ans = Max - Min + 1;
	for (int i=1; i<m; ++i)
		ans -= blank[i-1];
	printf("%d\n", ans);
}
int main()
{
	freopen("barn1.in", "r", stdin);
	freopen("barn1.out", "w", stdout);
	init();
	calc();
	return 0;
}
