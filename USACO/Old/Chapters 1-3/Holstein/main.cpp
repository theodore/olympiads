/*
ID:theodor8
PROB:holstein
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)
//#define Debug

int m, need[30], n, feed[20][30];
int main(){
	freopen("holstein.in", "r", stdin);
	freopen("holstein.out", "w", stdout);
	scanf("%d", &m);
	for (int i=0; i<m; ++i)
		scanf("%d", &need[i]);
	scanf("%d", &n);
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			scanf("%d", &feed[i][j]);
	//calc
	int ans_num(50), ans_arr[20];
	for (int choice=1; choice<(1<<n); ++choice){
		for (int i=0; i<m; ++i){
			int sum(0);
			for (int j=0; j<n; ++j)
				if ((1<<j)&choice)
					sum += feed[j][i];
			if (sum < need[i])
				goto cant;
		}
#ifdef Debug
		printf("Choice %d may be good\t", choice);
#endif
		//record ans
		int count, tmp_arr[20];
		count = 0;
		for (int i=0; i<n; ++i)
			if ((1<<i)&choice)
				tmp_arr[count++] = i;
		bool good;
		good = false;
		if (count<ans_num)
			good = true;
		if (count == ans_num)
			for (int i=0; i<count; ++i){
				if (tmp_arr[i] > ans_arr[i])
					break;
				else if (tmp_arr[i] < ans_arr[i]){
					good = true;
					break;
				}
			}
#ifdef Debug
		printf("%d %d\n", count, int(good));
#endif
		if (good){
			for (ans_num = count; count>=0; --count)
				ans_arr[count] = tmp_arr[count];
		}
cant:;
	}
	printf("%d", ans_num);
	for (int i=0; i<ans_num; ++i)
		printf(" %d", ans_arr[i]+1);
	printf("\n");
	return 0;
}
