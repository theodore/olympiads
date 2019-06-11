#include <cstdio>
#include <algorithm>

#define FDEC bool fl = false, fr = false;
#define FOR for (l += N - 1, r += N + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
#define FORL for (l >>= 1; l; l >>= 1)
#define FL if (fl)
#define FR if (fr)
#define IL if (~l & 1)
#define IR if (r & 1)
#define FLT fl = true
#define FRT fr = true
#define L l ^ 1
#define R r ^ 1
#define UP(a, b) (a = std::max(a, b))
#define RET return ret

const int maxN = 2049;

class ST_1D
{
public:
    static void init(const int n);
    void set(int y0, int y1, const int newv);
    int askmax(int y0, int y1) const;
private:
    static int N;
    int maxv[maxN], setv[maxN];
};

class ST_2D
{
public:
    static void init(const int n);
    void set(int x0, const int y0, int x1, const int y1, const int newv);
    int askmax(int x0, const int y0, int x1, const int y1) const;
private:
    static int N;
    ST_1D self[maxN], son[maxN];
};

void ST_2D::set(int l, const int y0, int r, const int y1, const int newv)
{
#if DB >= 1
    fprintf(stderr, "%d %d %d %d %d\n", l, y0, r, y1, newv);
#endif
    FDEC;
    FOR
    {
	FL son[l].set(y0, y1, newv);
	FR son[r].set(y0, y1, newv);
	IL self[L].set(y0, y1, newv), FLT;
	IR self[R].set(y0, y1, newv), FRT;
    }
    FL son[l].set(y0, y1, newv);
    FR son[r].set(y0, y1, newv);
    FORL son[l].set(y0, y1, newv);
}

int ST_2D::askmax(int l, const int y0, int r, const int y1) const
{
#if DB >= 1
    fprintf(stderr, "%d %d %d %d\n", l, y0, r, y1);
#endif
    int ret = 0; FDEC;
    FOR
    {
	FL UP(ret, self[l].askmax(y0, y1));
	FR UP(ret, self[r].askmax(y0, y1));
	IL UP(ret, son[L].askmax(y0, y1)), UP(ret, self[L].askmax(y0, y1)), FLT;
	IR UP(ret, son[R].askmax(y0, y1)), UP(ret, self[R].askmax(y0, y1)), FRT;
    }
    FL UP(ret, self[l].askmax(y0, y1));
    FR UP(ret, self[r].askmax(y0, y1));
    FORL UP(ret, self[l].askmax(y0, y1));
    RET;
}

void ST_1D::set(int l, int r, const int v)
{
    FDEC;
    FOR
    {
	FL UP(maxv[l], v);
	FR UP(maxv[r], v);
	IL UP(maxv[L], v), UP(setv[L], v), FLT;
	IR UP(maxv[R], v), UP(setv[R], v), FRT;
    }
    FL UP(maxv[l], v);
    FR UP(maxv[r], v);
    FORL UP(maxv[l], v);
}

int ST_1D::askmax(int l, int r) const
{
    int ret = 0; FDEC;
    FOR
    {
	FL UP(ret, setv[l]);
	FR UP(ret, setv[r]);
	IL UP(ret, maxv[L]), FLT;
	IR UP(ret, maxv[R]), FRT;
    }
    FL UP(ret, setv[l]);
    FR UP(ret, setv[r]);
    FORL UP(ret, setv[l]);
    RET;
}

int ST_1D::N;
void ST_1D::init(const int n)
{
    for (N = 4; N < n + 2; N <<= 1)
	;
}

int ST_2D::N;
void ST_2D::init(const int n)
{
    for (N = 4; N < n + 2; N <<= 1)
	;
}


ST_2D st;

int main()
{
    int n, m, _;
    scanf("%d%d%d", &n, &m, &_);
    ST_2D::init(n);
    ST_1D::init(m);
    for (int dx, dy, x, y, h; _--; )
    {
	scanf("%d%d%d%d%d", &dx, &dy, &h, &x, &y);
	st.set(x + 1, y + 1, x + dx, y + dy,
		st.askmax(x + 1, y + 1, x + dx, y + dy) + h);
    }
    printf("%d\n", st.askmax(1, 1, n, m));
}
