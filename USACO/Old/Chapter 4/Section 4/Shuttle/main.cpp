/*
PROB:shuttle
LANG:C++
*/
#include <iostream>

using namespace std;

typedef int situation[25];

int n;
int outputcount;

struct node{
	situation board;
	int blank;

	int pre;

	bool ll();
	bool lr();
	bool rl();
	bool rr();
	node goll();
	node golr();
	node gorl();
	node gorr();
	bool gotit();
	void output();
};

struct queue{
	node ele[112312];
	int front, back;

	 queue();
	void insert(node);
	node pop();
	bool empty();
} q;

bool node::ll(){
	if (blank < 2)
		return false;
	if (board[blank-1] != 0)
		return false;
	if (board[blank-2] != 1)
		return false;
	return true;
}

bool node::lr(){
	if (!blank)
		return false;
	return board[blank-1]==1;
}

bool node::rl(){
	if (blank == 2*n)
		return false;
	return board[blank+1]==0;
}

bool node::rr(){
	if (blank >= 2*n-1)
		return false;
	if (board[blank+1] != 1)
		return false;
	if (board[blank+2] != 0)
		return false;
	return true;
}

node node::goll(){
	node ret = *this;
	ret.board[blank] = 1;
	ret.blank -= 2;
	return ret;
}

node node::golr(){
	node ret = *this;
	ret.board[blank] = 1;
	--ret.blank;
	return ret;
}

node node::gorl(){
	node ret = *this;
	ret.board[blank] = 0;
	++ret.blank;
	return ret;
}

node node::gorr(){
	node ret = *this;
	ret.board[blank] = 0;
	ret.blank += 2;
	return ret;
}

bool node::gotit(){
	if (blank != n)
		return false;
	for (int i=0; i<n; ++i)
		if (board[i])
			return false;
	for (int i=n+1; i<=2*n; ++i)
		if (!board[i])
			return false;
	return true;
}

void node::output(){
	if (pre > 0)
		q.ele[pre].output();
	if (outputcount % 20)
		printf(" ");
	printf("%d", blank+1);
	++outputcount;
	if (outputcount % 20 == 0)
		printf("\n");
}

queue::queue()
	: front(0), back(0){
}

void queue::insert(node x){
	ele[back++] = x;
}

node queue::pop(){
	return ele[front++];
}

bool queue::empty(){
	return front==back;
}

// from 111_000 -> 000_111
int main()
{
	freopen("shuttle.in", "r", stdin);
	freopen("shuttle.out", "w", stdout);
	scanf("%d", &n);
	node first;
	for (int i=0; i<2*n+1; ++i){
		first.board[i] = i<n ? 1 : 0;
	}
	first.blank = n;
	first.pre = -1;
	q.insert(first);

	while (!q.empty()){
		node now = q.pop();
		if (now.ll()){
			node next = now.goll();
			next.pre = q.front - 1;
			if (next.gotit()){
				next.output();
				goto outside;
			}
			q.insert(next);
		}
		if (now.lr()){
			node next = now.golr();
			next.pre = q.front - 1;
			if (next.gotit()){
				next.output();
				goto outside;
			}
			q.insert(next);
		}
		if (now.rl()){
			node next = now.gorl();
			next.pre = q.front - 1;
			if (next.gotit()){
				next.output();
				goto outside;
			}
			q.insert(next);
		}
		if (now.rr()){
			node next = now.gorr();
			next.pre = q.front - 1;
			if (next.gotit()){
				next.output();
				goto outside;
			}
			q.insert(next);
		}
	}
outside:
	if (outputcount % 20)
		printf("\n");
    return 0;
}
