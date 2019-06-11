#include <cstdio>
#include <cstdlib>

//const int mod = 1000000000;
const int mod = 100;

int main()
{
    int r;
    scanf("%d", &r);
    srand(r);
    printf("%d %d\n", rand() % mod + 1, rand() % mod + 1);
}
