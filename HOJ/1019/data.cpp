#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

string str[] = {"AB", "AC", "BA", "BC", "CA", "CB"};

void out()
{
    for (int i = 0; i < 6; ++i)
	printf("%s ", str[i].c_str());
    puts("");
}

int main()
{
    int n;
    scanf("%d", &n);
    do {
	printf("%d\n", n);
	out();
    } while (next_permutation(str, str + 6));
}
