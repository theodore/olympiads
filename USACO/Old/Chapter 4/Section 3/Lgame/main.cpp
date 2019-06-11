/*
PROB:lgame
LANG:C++
*/
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

FILE* Dict = fopen("lgame.dict", "r");
const int Hash[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

char code[11];
int cnt[11];

char dict[38511][11];
int num, highest;
int score[38511];

void Count(char* code, int* cnt){
	for (int i=0; i<strlen(code); ++i)
		for (int j=0; j<strlen(code); ++j)
			if (code[i] == code[j])
				++cnt[i];
}

bool good(char* x){
	int cntme[11];
	memset(cntme, 0, sizeof(cntme));
	Count(x, cntme);
	for (int i=0; i<strlen(x); ++i){
		int pos = -1;
		for (int j=0; j<strlen(code); ++j)
			if (x[i] == code[j])
				pos = j;
		if (cntme[i] > cnt[pos])
			return false;
	}
	return true;
}

int main()
{
	freopen("lgame.in", "r", stdin);
	freopen("lgame.out", "w", stdout);
	scanf("%s", code);
	sort(code, code+strlen(code));
	Count(code, cnt);
	char temp[11];
	for (fscanf(Dict, "%s", temp); temp[0]!='.'; fscanf(Dict, "%s", temp)){
		if (good(temp)){
			for (int i=0; i<strlen(temp); ++i)
				score[num] += Hash[temp[i]-'a'];
			if (highest < score[num])
				highest = score[num];
			strcpy(dict[num++], temp);
		}
	}







	char t[17];
	for (int i=0; i<num; ++i)
		for (int j=i+1; j<num; ++j)
			if (score[i] + score[j] > highest){
				strcpy(t, dict[i]);
				for (int a=strlen(t), b=0; b<=strlen(dict[j]); ++a, ++b)
					t[a] = dict[j][b];
				if (good(t))
					highest = score[i] + score[j];
			}








	printf("%d\n", highest);
	int delta;
	for (int i=0; i<num; ++i)
		if (score[i] == highest)
			printf("%s\n", dict[i]);
		else if ((delta = highest - score[i]) >= 3)
			for (int j=i+1; j<num; ++j)
				if (score[j] == delta){
					char t[11];
					strcpy(t, dict[i]);
					strcat(t, dict[j]);
					if (good(t))
						printf("%s %s\n", dict[i], dict[j]);
				}
	return 0;
}
