/*
PROB:cryptcow
LANG:C++
*/
#include <iostream>
#include <cstring>
#define COW(x) ((x)=='C' || (x)=='O' || (x)=='W')

using namespace std;

const char* ori = "Begin the Escape execution at the Break of Dawn";
char code[100];
int dep;

/////////////////////////////////////////////////
#define MOD 99991
struct node{
	node(char*);
	char str[100];
	node* next;
};
node::node(char* a){
	strcpy(str, a);
	next = 0;
}

////////
class chash{
	node* ele[MOD];
	int h(char*);
 public:
	bool in(char*);
	void insert(char*);
} Hash;

int chash::h(char* code){
	int ret = 0;
	for (int i=0; i<strlen(code); ++i)
		ret = ret * 256 + code[i];
	return (ret % MOD + MOD) % MOD;
}

bool chash::in(char* code){
	for (node* ind=ele[h(code)]; ind; ind=ind->next)
		if (!strcmp(code, ind->str))
			return true;
	return false;
}

void chash::insert(char* code){
	node* ind = ele[h(code)];
	if (!ind)
		ind = new node(code);
	else{
		while (ind->next)
			ind = ind->next;
		ind->next = new node(code);
	}
}
#undef MOD
///////////////////////////////////////////////////////

inline void zero(){
	printf("0 0\n");
	exit(0);
}

//pruning fuctions
bool presuf(char* code){
	int pre, suf;
	for (pre=0; !COW(code[pre]); ++pre);
	for (int i=0; i<pre; ++i)
		if (ori[i] != code[i])
			return false;
	for (suf=strlen(code)-1; !COW(code[suf]); --suf);
	for (int i=suf+1, j=strlen(ori)-strlen(code)+i; i<strlen(code); ++i, ++j)
		if (ori[j] != code[i])
			return false;
	return true;
}
bool in(char* code, int s, int e){
	for (int i=0; i<=strlen(ori)-e+s; ++i){
		for (int j=i, k=s; k<e; ++j, ++k)
			if (ori[j] != code[k])
				goto next;
		return true;
next:;
	}
	return false;
}
bool part(char* code){
	int s, e;
	for (s=0; !COW(code[s]); ++s);
	for (; ; s=e){
		for (e=s+1; e<strlen(code)&&!COW(code[e]); ++e);
		if (e == strlen(code))
			break;
		if (!in(code, s+1, e))
			return false;
	}
	return true;
}

void init(){
	cin.getline(code, 100);
	if ((strlen(code) - strlen(ori)) % 3)
		zero();
	dep = (strlen(code) - strlen(ori)) / 3;
	if (!dep){
		if (strcmp(ori, code))
			zero();
		else{
			printf("1 0\n");
			exit(0);
		}
	}
	int C(0), W(0), O(0);
	for (int i=0; i<strlen(code); ++i)
		switch(code[i]){
		case 'C':
			++C;
			break;
		case 'O':
			++O;
			break;
		case 'W':
			++W;
			break;
		}
	if (!(C==dep && O==dep && W==dep))
		zero();
	if (!presuf(code) || !part(code))
		zero();
}

//fuctions to get it
void change(char* code, int c, int o, int w){
	char t[100], e[100];
	strcpy(t, code+o+1);
	t[w-o-1] = '\0';
	strcpy(e, code+c+1);
	e[o-c-1] = '\0';
	strcat(t, e);
	strcat(t, code+w+1);
	code[c] = '\0';
	strcat(code, t);
}
inline bool good(char* code){
	return presuf(code) && part(code);
}
void search(char* code, int now){
	if (now == dep){
		if (!strcmp(ori, code)){
			printf("1 %d\n", dep);
			exit(0);
		}
		return;
	}
	if (Hash.in(code))
		return;
	Hash.insert(code);
	for (int o=0; o<strlen(code); ++o)
		if (code[o] == 'O')
			for (int c=0; c<o; ++c)
				if (code[c] == 'C')
					for (int w=strlen(code)-1; w>o; --w)
						if (code[w] == 'W'){
							char t[100];
							strcpy(t, code);
							change(t, c, o, w);
							if (now==dep-1 || good(t))
								search(t, now+1);
						}
}

void getit(){
	char t[100];
	strcpy(t, code);
	search(t, 0);
	zero();
}

int main(){
	freopen("cryptcow.in", "r", stdin);
	freopen("cryptcow.out", "w", stdout);
	init();
	getit();
	return 0;
}
