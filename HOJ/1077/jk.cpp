/*
 * $File: scale.cpp
 * $Date: Sat Jan 23 14:37:53 2010 CST
 */
#define INPUT	"scale.in"
#define OUTPUT	"scale.out"

#define STDIO

#include <cstdio>
#include <cstring>

namespace Solve
{
	const int NVTX_MAX = 55, NARC_MAX = NVTX_MAX * NVTX_MAX * 2,
			MAX_WEIGHT = 3, MIN_WEIGHT = 1;

	int poise_vtx_num[NVTX_MAX];
	void merge_poise(int a, int b);
	int calc_poise_vtx_num(int n);

	struct Arc
	{
		int tvtx, next;
	};
	Arc arc[NARC_MAX];
	int narc;
	bool arc_exist[NVTX_MAX][NVTX_MAX];
	void insert_arc(int svtx, int tvtx);

	struct Vertex
	{
		int ihead, ohead; // in arc, out arc
	};
	Vertex graph[NVTX_MAX];
	int weight[NVTX_MAX];

	int maxmize(int vtx);
	int minmize(int vtx);

	int c1, c2, c3;
	void calc(int a1, int a2, int b1, int b2);

	void solve(FILE *fin, FILE *fout);
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int npoise, a, b;
	fscanf(fin, "%d %d %d", &npoise, &a, &b);
	a --;
	b --;
	for (int i = 0; i < npoise; i ++)
		poise_vtx_num[i] = i;
	char matrix[NVTX_MAX][NVTX_MAX];
	for (int i = 0; i < npoise; i ++)
	{
		fscanf(fin, "%s", matrix[i]);
		for (int j = 0; j < npoise; j ++)
			if (matrix[i][j] == '=')
				merge_poise(i, j);
	}
	for (int i = 0; i < npoise; i ++)
		calc_poise_vtx_num(i);
	for (int i = 0; i < npoise; i ++)
		for (int j = 0; j < npoise; j ++)
			if (matrix[i][j] == '+')
				insert_arc(poise_vtx_num[i], poise_vtx_num[j]);
			else if (matrix[i][j] == '-')
				insert_arc(poise_vtx_num[j], poise_vtx_num[i]);
	for (int i = 0; i < npoise; i ++)
		for (int j = i + 1; j < npoise; j ++)
			if (i != a && i != b && j != a && j != b)
				calc(a, b, i, j);
	fprintf(fout, "%d %d %d\n", c1, c2, c3);
}

void Solve::insert_arc(int svtx, int tvtx)
{
	if (arc_exist[svtx][tvtx])
		return;
	arc_exist[svtx][tvtx] = true;

	narc ++;
	arc[narc].tvtx = tvtx;
	arc[narc].next = graph[svtx].ohead;
	graph[svtx].ohead = narc;

	narc ++;
	arc[narc].tvtx = svtx;
	arc[narc].next = graph[tvtx].ihead;
	graph[tvtx].ihead = narc;
}

void Solve::calc(int a1, int a2, int b1, int b2)
{
	a1 = poise_vtx_num[a1];
	a2 = poise_vtx_num[a2];
	b1 = poise_vtx_num[b1];
	b2 = poise_vtx_num[b2];
	if (a1 > a2)
	{
		int register tmp = a1;
		a1 = a2;
		a2 = tmp;
	}
	if (b1 > b2)
	{
		int register tmp = b1;
		b1 = b2;
		b2 = tmp;
	}
	if (a1 == b1 && a2 == b2)
	{
		c2 ++;
		return;
	}
	if (a1 == b1)
		a1 = b1 = NVTX_MAX - 1; // maxmize() or minmize() will return 0
	if (a1 == b2)
		a1 = b2 = NVTX_MAX - 1;
	if (a2 == b1)
		a2 = b1 = NVTX_MAX - 1;
	if (a2 == b2)
		a2 = b2 = NVTX_MAX - 1;

	bool t1 = 0, t2 = 0, t3 = 0;
	for (int i = 0; i < 16; i ++)
	{
		memset(weight, 0, sizeof(weight));
		int d = 0;
		if (i & 1)
			d += maxmize(a1);
		else d += minmize(a1);
		if (i & 2)
			d += maxmize(a2);
		else d += minmize(a2);
		if (i & 4)
			d -= maxmize(b1);
		else d -= minmize(b1);
		if (i & 8)
			d -= maxmize(b2);
		else d -= minmize(b2);

		if (d > 0)
		{
			if (t2 || t3)
				return;
			t1 = true;
		}
		if (d == 0)
		{
			if (t1 || t3)
				return;
			t2 = true;
		}
		if (d < 0)
		{
			if (t1 || t2)
				return;
			t3 = true;
		}
	}
	if (t1)
		c1 ++;
	else if (t2)
		c2 ++;
	else if (t3)
		c3 ++;
}

int Solve::maxmize(int vtx)
{
	if (weight[vtx])
		return weight[vtx];
	int min = MAX_WEIGHT + 1;
	for (int i = graph[vtx].ihead; i; i = arc[i].next)
	{
		int register tmp = maxmize(arc[i].tvtx);
		if (tmp < min)
			min = tmp;
	}
	return weight[vtx] = min - 1;
}

int Solve::minmize(int vtx)
{
	if (weight[vtx])
		return weight[vtx];
	int max = MIN_WEIGHT - 1;
	for (int i = graph[vtx].ohead; i; i = arc[i].next)
	{
		int register tmp = minmize(arc[i].tvtx);
		if (tmp > max)
			max = tmp;
	}
	return weight[vtx] = max + 1;
}

void Solve::merge_poise(int a, int b)
{
	int register ar = calc_poise_vtx_num(a), br = calc_poise_vtx_num(b);
	if (ar != br)
		poise_vtx_num[ar] = br;
}

int Solve::calc_poise_vtx_num(int n)
{
	if (poise_vtx_num[n] == n)
		return n;
	return poise_vtx_num[n] = calc_poise_vtx_num(poise_vtx_num[n]);
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, fout);
	fclose(fin);
	fclose(fout);
#endif
}

