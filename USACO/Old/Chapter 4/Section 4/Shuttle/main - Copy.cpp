/*
PROB:shuttle
LANG:C++
*/
#include <iostream>

using namespace std;

typedef int situation[31];

int n;

struct node{
	situation board;
	int blank;

	int priority;
	int pre, where;

	bool ll();
	bool lr();
	bool rl();
	bool rr();
	void goll();
	void golr();
	void gorl();
	void gorr();
	bool operator==(situation);
	void output();
};

class Heap{
	int num;
	node state[1000013];
 public:
	 Heap();
  	void insert(node);
  	node pop();
  	bool empty();
  	node operator[](int);
} q;


// from 111 000 -> 000 111
int main()
{
	freopen("shuttle.in", "r", stdin);
	freopen("shuttle.out", "w", stdout);
	scanf("%d", &n);
	node first;
	situation goal;
	for (int i=0; i<2*n+1; ++i)
		first.board[i] = i<n ? 1 : 0;
	first.blank = n;
	first.pre = -1;
	first.priority = n * n;
	q.insert(first);

	while (!q.empty()){
		node now = q.pop();
		if (now.ll()){
			node next = now.goll();
			if (next == goal)
				next.output();
			q.insert(next);
		}
		if (now.lr()){
			node next = now.golr();
			if (next == goal)
				next.output();
			q.insert(next);
		}
		if (now.rl()){
			node next = now.gorl();
			if (next == goal)
				next.output();
			q.insert(next);
		}
		if (now.rr()){
			node next = now.gorr();
			if (next == goal)
				next.output();
			q.insert(next);
		}
	}
    return 0;
}
