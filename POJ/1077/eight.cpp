#include <cstdio>
#include <queue>

struct state_t
{
	int a[5][5];
	state_t();
	state_t(const state_t&);
	// remember to add 1
	int hash();
	bool get_state(int, state_t&);
};

state_t::state_t()
{
}

state_t::state_t(const state_t& x)
{
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			a[i][j] = x.a[i][j];
}

int fact[13];

int state_t::hash()
{
	int ret(0);
	for (int i = 2; i <= 9; ++i)
	{
		int t(0);
		for(int j = 1; j < i; ++j)
			if (a[(j - 1) / 3 + 1][(j - 1) % 3 + 1] < a[(i - 1) / 3 + 1][(i - 1) % 3 + 1])
				++t;
		ret += fact[i - 1] * t;
	}
	return ret;
}

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

bool state_t::get_state(int dir, state_t& next)
{
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j)
			if (a[i][j] == 0)
			{
				int nx = i + dx[dir],
					ny = j + dy[dir];
				if (nx > 0 && nx <= 3 && ny > 0 && ny <= 3)
				{
					for (int u = 1; u <= 3; ++u)
						for (int v = 1; v <= 3; ++v)
							next.a[u][v] = a[u][v];
					next.a[i][j] = next.a[nx][ny];
					next.a[nx][ny] = 0;
					return true;
				}
				else
					return false;
			}
	//assert(0);
	return false;
}

const int maxs(362999);
state_t st, goal;
bool vis[maxs];
int pre[maxs][2];
int goal_hash;

void init()
{
	fact[0] = 1;
	for (int i = 1; i < 10; ++i)
		fact[i] = fact[i - 1] * i;
	char str[3];
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j)
		{
			scanf("%s", str);
			if (str[0] == 'x')
				st.a[i][j] = 0;
			else
				st.a[i][j] = str[0] - '0';
		}
	for (int i = 1; i <= 3; ++i)
		for (int j = 1; j <= 3; ++j)
			goal.a[i][j] = (i - 1) * 3 + j;
	goal.a[3][3] = 0;
	goal_hash = goal.hash();
}

std::queue <state_t> q;

void go()
{
	q.push(st);
	vis[st.hash()] = true;
	int t;
	while (!q.empty())
	{
		static state_t now, next;
		now = q.front();
		q.pop();
		for (int dir = 0; dir < 4; ++dir)
		{
			if (now.get_state(dir, next))
			{
				if (vis[t = next.hash()])
					continue;
				pre[next.hash()][0] = now.hash();
				pre[t][1] = dir;
				vis[t] = true;
				q.push(next);
				if (t == goal_hash)
					return;
			}
		}
	}
}

const char chr[] = {'u', 'r', 'd', 'l'};

void output(int x)
{
	if (pre[x][0])
	{
		output(pre[x][0]);
		putchar(chr[pre[x][1]]);
	}
}

int main()
{
#ifdef GDB
	freopen("in", "r", stdin);
#endif
	init();
	go();
	// maybe goal == st?
	if (!pre[goal.hash()][0])
		printf("unsolvable\n");
	else
	{
		output(goal.hash());
		putchar('\n');
	}
	return 0;
}
