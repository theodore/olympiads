/*
PROB:heritage
LANG:C++
*/
#include <iostream>
#include <cstring>

using namespace std;

char in[30], pre[30], post[30];

int change(char* in, char* pre, char* post, int start){
	if (!strlen(in))
		return start;
	char In[30], Pre[30];
	strcpy(In, in);
	char* foo = strchr(In, pre[0]);
	*foo = '\0';
	strcpy(Pre, pre);
	int til = change(In, Pre+1, post, start);
	int len = strlen(In);
	strcpy(In, in);
	til = change(In+len+1, Pre+len+1, post, til);
	post[til++] = Pre[0];
	post[til+1] = '\0';
	return til;
}

int main(){
	freopen("heritage.in", "r", stdin);
	freopen("heritage.out", "w", stdout);
	scanf("%s%s", in, pre);
	change(in, pre, post, 0);
	printf("%s\n", post);
	return 0;
}
//int main(){
//	int* a[5] = new int[5][5];
//	for (int i=0; i<5; ++i)
//		cin >> a[i][3];
//	cout << a[0][3] << endl << a[4][3] << endl;
//}
