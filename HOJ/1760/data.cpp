#include <cstdio>
#include <cstdlib>
#include <vector>

typedef std::vector<int> Vint;

int m;

class Polygon {
public:
    Polygon(int s)
    {
        for (int i = 1; i <= s; i++)
            v.push_back(i);
    }

    Polygon(Vint z)
    {
        v = z;
    }

    void work()
    {
        if (v.size() == 3) {
            printf("%d %d %d %d\n", v[0], v[1], v[2], rand() % m + 1);
        } else {
            int a = rand() % v.size(), b;
            do b = rand() % v.size();
            while (abs(a - b) < 2 || abs(a - b) == v.size() - 1);
            if (a > b) std::swap(a, b);
            Vint x, z;
            for (int i = a; i <= b; i++)
                z.push_back(v[i]);
            Polygon(z).work();
            for (int i = 0; i <= a; i++)
                x.push_back(v[i]);
            for (int i = b; i < v.size(); i++)
                x.push_back(v[i]);
            Polygon(x).work();
        }
    }
private:
    Vint v;
};

int main()
{
    int n, r;
    scanf("%d%d%d", &n, &m, &r);
    printf("%d\n", n);
    srand(r);
    Polygon z(n);
    z.work();
}
