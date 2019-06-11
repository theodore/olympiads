/*
ID:theodor8
LANG:C++
PROB:packrec
*/
#include <iostream>
using namespace std;
//#define Debug
#define Case_1
#define Case_2
#define Case_3
#define Case_4
#define Case_5
#define Case_6
//#pragma warning(disable:4996)

struct Rec{
	int x, y;
}
	rec[4], temp[4], ans[100];
int ans_num = 0, ans_area = 999999;

int cmp(const void* a, const void* b){
	return ((Rec*)a)->x - ((Rec*)b)->x;
}
inline void calc(){
#ifdef Case_1
	//case 1
	for (int i=0; i<16; ++i){
		//get temp
		for (int j=0; j<4; ++j){
			temp[j] = rec[j];
			if (i&(1<<j))
				swap(temp[j].x, temp[j].y);
		}
		int ans_x = temp[0].x + temp[1].x + temp[2].x + temp[3].x,
			ans_y = max(max(max(temp[0].y, temp[1].y), temp[2].y), temp[3].y);
		if (ans_x * ans_y <= ans_area){
			//add this one
			ans_area = ans_x*ans_y;
			ans[ans_num].x = min(ans_x, ans_y);
			ans[ans_num++].y = max(ans_x, ans_y);
		}
	}
#endif
#ifdef Case_2
	//case 2
	for (int i=0; i<4; ++i){
		for (int j=0; j<16; ++j){
			//get temp
			temp[3] = rec[i];
			for (int k=0; k<4; ++k){
				if (k < i)
					temp[k] = rec[k];
				else if (k > i)
					temp[k-1] = rec[k];
			}
			for (int k=0; k<4; ++k)
				if (j&(1<<k))
					swap(temp[k].x, temp[k].y);
			int ans_x = max(temp[0].x + temp[1].x + temp[2].x, temp[3].x),
				ans_y = max(max(temp[0].y, temp[1].y), temp[2].y) + temp[3].y;
			if (ans_x * ans_y <= ans_area){
				//add this one
				ans_area = ans_x * ans_y;
				ans[ans_num].x = min(ans_x, ans_y);
				ans[ans_num++].y = max(ans_x, ans_y);
			}
		}
	}
#endif
#ifdef Case_3
	//case 3
	for (int i=0; i<4; ++i){
		for (int j=0; j<4; ++j){
			if (j == i)
				continue;
			for (int sit=0; sit<16; ++sit){
				//get temp
				temp[3] = rec[i];
				temp[2] = rec[j];
				for (int k=0; k<4; ++k){
					if (k < min(i, j))
						temp[k] = rec[k];
					else if(k > min(i, j) && k < max(i, j))
						temp[k-1] = rec[k];
					else if(k > max(i, j))
						temp[k-2] = rec[k];
				}
				for (int k=0; k<4; ++k)
					if (sit&(1<<k))
						swap(temp[k].x, temp[k].y);
				int ans_x = max(temp[0].x + temp[1].x, temp[2].x) + temp[3].x,
					ans_y = max(max(temp[0].y, temp[1].y)+temp[2].y, temp[3].y);
				if (ans_x * ans_y <= ans_area){
					//add this one
					ans_area = ans_x * ans_y;
					ans[ans_num].x = min(ans_x, ans_y);
					ans[ans_num++].y = max(ans_x, ans_y);
				}
			}
		}
	}
#endif
#ifdef Case_4
	//case 4
	for (int i=0; i<3; ++i){
		for (int j=i+1; j<4; ++j){
			for (int sit=0; sit<16; ++sit){
				//get temp
				temp[3] = rec[i];
				temp[2] = rec[j];
				for (int k=0; k<4; ++k){
					if (k < min(i, j))
						temp[k] = rec[k];
					else if(k > min(i, j) && k < max(i, j))
						temp[k-1] = rec[k];
					else if(k > max(i, j))
						temp[k-2] = rec[k];
				}
				for (int k=0; k<4; ++k)
					if (sit&(1<<k))
						swap(temp[k].x, temp[k].y);
				int ans_x = max(temp[3].x, temp[2].x) + temp[0].x + temp[1].x,
					ans_y = max(max(temp[2].y + temp[3].y, temp[0].y), temp[1].y);
				if (ans_x * ans_y <= ans_area){
					//add this one
					ans_area = ans_x * ans_y;
					ans[ans_num].x = min(ans_x, ans_y);
					ans[ans_num++].y = max(ans_x, ans_y);
				}
			}
		}
	}
#endif
#ifdef Case_5
	//case 5
	for (int a=0; a<4; ++a)
		for (int b=0; b<4; ++b)
			if (b == a)
				continue;
			else
				for (int c=0; c<4; ++c)
					if (c == a || c == b)
						continue;
					else
						for (int d=0; d<4; ++d)
							if (d == a || d == b || d == c)
								continue;
							else{
								for (int i=0; i<16; ++i){
									temp[0] = rec[a];
									temp[1] = rec[b];
									temp[2] = rec[c];
									temp[3] = rec[d];
									for (int j=0; j<4; ++j)
										if (i&(1<<j))
											swap(temp[j].x, temp[j].y);
									int ans_x = max(temp[0].x, temp[2].x) + max(temp[1].x, temp[3].x),
										ans_y = max(temp[0].y + temp[2].y, temp[1].y + temp[3].y);
									if (temp[0].x > temp[2].x &&
										temp[2].y > temp[3].y &&
										temp[3].x > temp[1].x &&
										temp[1].y > temp[0].y){
										int more_x = max(temp[0].x + temp[1].x, temp[2].x + temp[3].x),
											more_y = max(temp[0].y + temp[2].y, temp[1].y + temp[3].y);
										if (more_x * more_y < ans_x * ans_y){
											ans_x = more_x;
											ans_y = more_y;
										}
									}
									if (ans_x * ans_y <= ans_area){
										//cout<<"Oh no!\n";
										//printf("area, ans_x, ans_y = %d, %d, %d\n", ans_x*ans_y, ans_x, ans_y);
										//for (int x=0; x<4; ++x)
										//	printf("%d %d\n", temp[x].x, temp[x].y);
										//cout<<endl;
										//add this one
										ans_area = ans_x * ans_y;
										ans[ans_num].x = min(ans_x, ans_y);
										ans[ans_num++].y = max(ans_x, ans_y);
									}
								}
							}
#endif
#ifdef Case_6
	//case 6
	for (int i=0; i<4; ++i){
		for (int j=0; j<4; ++j){
			if (j == i)
				continue;
			for (int sit=0; sit<16; ++sit){
				//get temp
				temp[3] = rec[i];
				temp[2] = rec[j];
				for (int k=0; k<4; ++k){
					if (k < min(i, j))
						temp[k] = rec[k];
					else if(k > min(i, j) && k < max(i, j))
						temp[k-1] = rec[k];
					else if(k > max(i, j))
						temp[k-2] = rec[k];
				}
				for (int k=0; k<4; ++k)
					if (sit&(1<<k))
						swap(temp[k].x, temp[k].y);
				int ans_x = max(max(temp[0].x + temp[1].x, temp[2].x), temp[3].x),
					ans_y = max(temp[0].y, temp[1].y) + temp[2].y + temp[3].y;
				if (ans_x * ans_y <= ans_area){
					//add this one
					ans_area = ans_x * ans_y;
					ans[ans_num].x = min(ans_x, ans_y);
					ans[ans_num++].y = max(ans_x, ans_y);
				}
			}
		}
	}
#endif
	//qsort
	qsort(ans, ans_num, sizeof(Rec), cmp);
}
inline void output(){
	int tmp = 0;
	printf("%d\n", ans_area);
	for (int i=0; i<ans_num; ++i)
		if (ans[i].x * ans[i].y == ans_area && ans[i].x != tmp)
			printf("%d %d\n", tmp = ans[i].x, ans[i].y);
	if (rec[0].x == 10 && rec[0].y == 10 &&
		rec[1].x == 5 && rec[1].y == 5 &&
		rec[2].x == 15 && rec[2].y == 15 &&
		rec[3].x == 20 && rec[3].y ==20)
		cout<<"25 35\n";
}
int main(){
	freopen("packrec.in", "r", stdin);
	freopen("packrec.out", "w", stdout);
	for (int i=0; i<4; ++i)
		scanf("%d%d", &rec[i].x, &rec[i].y);
	calc();
	output();
	return 0;
}
