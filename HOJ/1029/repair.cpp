#include <cstdio>
#include <algorithm>
#include <queue>

struct Building {
    int duration, deadline;
    bool operator<(const Building& z) const
    { return deadline < z.deadline; }
};

const int Max_n = 150003;
int n;
Building ymf[Max_n];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &ymf[i].duration, &ymf[i].deadline);
    std::sort(ymf, ymf + n);

    int sum = 0;
    std::priority_queue<int> q;
    for (int i = 0, t; i < n; i++)
        if (sum + ymf[i].duration <= ymf[i].deadline) {
            q.push(ymf[i].duration);
            sum += ymf[i].duration;
        } else if (!q.empty() && (t = q.top()) > ymf[i].duration) {
            sum -= t - ymf[i].duration;
            q.pop();
            q.push(ymf[i].duration);
        }

    printf("%d\n", q.size());
}
