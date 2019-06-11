#include <bits/stdc++.h>

using namespace std;

string gen(int n)
{
    if (n == 0)
        return (rand() % 100000 < 1 ? "1" : "0");
    string s[4];
    for (int i = 0; i < 4; i++)
        s[i] = gen(n - 1);
    if (s[0] == s[1] && s[2] == s[3] && s[0] == s[2])
        return s[0];
    else
        return "2" + s[0] + s[1] + s[2] + s[3];
}

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    srand(r);
    cout << n << endl << gen(n) << endl;
}
