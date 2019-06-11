/*
ID:theodor8
PROB:cowtour
LANG:C++
*/
#include <iostream>
#include <cmath>
using namespace std;
#pragma warning(disable:4996)
#define Debug
#define WTF
#define infinity 999999

#ifdef WTF
double wtf[155];
#endif
int n;
bool connected[155][155];
double ans(infinity), dis[155][155];
int of_field[155], field_num;
struct{
	int x, y;
}	pas[155];

void flood(const int& x){
	of_field[x] = field_num;
	for (int i=0; i<n; ++i)
		if (connected[x][i] && !of_field[i])
			flood(i);
}
inline void floyd(){
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			if (connected[i][j])
				dis[i][j] = hypot(pas[i].x-pas[j].x, pas[i].y-pas[j].y);
			else if (i==j)
				dis[i][j] = 0;
			else
				dis[i][j] = infinity;
	for (int k=0; k<n; ++k)
		for (int i=0; i<n; ++i)
			for (int j=0; j<n; ++j)
				if (dis[i][j] > dis[i][k]+dis[k][j])
					dis[i][j] = dis[i][k] + dis[k][j];
}
inline void find(){
	for (int i=0; i<n; ++i)
		for (int j=i+1; j<n; ++j){
			if (of_field[i] == of_field[j])
				continue;
			double t(hypot(pas[i].x-pas[j].x, pas[i].y-pas[j].y));
			int fi(i), fj(j);
			for (int k=0; k<n; ++k)
				if (of_field[k]==of_field[i] && dis[i][k]>dis[i][fi])
					fi = k;
				else if(of_field[k]==of_field[j] && dis[j][k]>dis[j][fj])
					fj = k;
			t += dis[i][fi] + dis[j][fj];
#ifdef WTF
			wtf[i] = dis[i][fi];
			wtf[j] = dis[j][fj];
#endif
			if (t<ans)
				ans = t;
		}
}
int main(){
	freopen("cowtour.in", "r", stdin);
	freopen("cowtour.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<n; ++i)
		scanf("%d%d", &pas[i].x, &pas[i].y);
	char qwertyuiop;
	scanf("%c", &qwertyuiop);
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j){
			scanf("%c", &qwertyuiop);
			connected[i][j] = qwertyuiop=='1';
		}
		scanf("%c", &qwertyuiop);
	}
	for (int i=0; i<n; ++i)
		if (!of_field[i]){
			++field_num;
			flood(i);
		}
	floyd();
	find();
#ifdef WTF
	double Wtf(wtf[0]);
	for (int i=1; i<n; ++i)
		if (wtf[i] > Wtf)
			Wtf = wtf[i];
	if (ans < Wtf){
		//printf("Why!\n");
		ans = Wtf;
	}
#endif
	printf("%.6f\n", ans);
	return 0;
}
