#include <stdio.h>
#include <deque>
#include <list>

const int Max_n = 1000007;
int n, m;
int s[Max_n], pattern[Max_n], text[Max_n];
int fail[Max_n];
int less[Max_n], greater[Max_n];

bool neq(int pos, int* arr) // position in pattern, array to compare
{
    if (less[pos] && arr[less[pos]] >= arr[pos])
        return true;
    if (greater[pos] && arr[greater[pos]] <= arr[pos])
        return true;
    return false;
}

void Init()
{
    typedef std::list<int>::iterator LI;
    std::list<int> L;
    static LI iter[Max_n];

    for (int i = 1; i <= n; i++)
        L.push_back(s[i]), iter[i] = --L.end();
    for (int i = n; i >= 1; i--) {
        LI z;
        if ((z = iter[pattern[i]]) != L.begin())
            less[i] = *--z;
        if (++(z = iter[pattern[i]]) != L.end())
            greater[i] = *z;
        L.erase(iter[pattern[i]]);
    }

    fail[0] = -1;
    for (int i = 1; i <= n; i++) {
        for (int& j = fail[i] = fail[i - 1];
                j >= 0 && neq(j + 1, pattern + i - j - 1); j = fail[j])
            ;
        fail[i]++;
    }

#if DB & 1
    for (int i = 1; i <= n; i++)
        fprintf(stderr, "%d\n", fail[i]);
    fprintf(stderr, "\n\n");
#endif
}

void Work()
{
    std::deque<int> ans;

    for (int i = 1, j = 0; i <= m; i++) {
        while (j >= 0 && neq(j + 1, text + i - j - 1))
            j = fail[j];
#if DB & 2
        fprintf(stderr, "%d: %d\n", i, j + 1);
#endif
        if (++j == n) {
            ans.push_back(i - n + 1);
            j = fail[j];
        }
    }

    printf("%d\n", ans.size());
    if (!ans.empty()) {
        int t = ans.back();
        ans.resize(ans.size() - 1);
        for (std::deque<int>::iterator i = ans.begin(); i != ans.end(); ++i)
            printf("%d ", *i);
        printf("%d\n", t);
    } else {
        puts("");
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &s[i]), pattern[s[i]] = i;
    for (int i = 1; i <= m; i++)
        scanf("%d", &text[i]);

    Init();
    Work();
}
