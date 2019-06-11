#include <iostream>
#define MAXN 4010
#define MAXP 2010
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define INFINITE (1<<30)
#define MAX(a,b) ((a) > (b) ? (a) : (b))

using namespace std;

int T,MaxP,W;
int AP[MAXN+1], BP[MAXN+1], AS[MAXN+1], BS[MAXN+1];
int n;
void Init(){
     scanf("%d%d%d",&n,&MaxP,&W);
     for (int i = 1; i<=n; i++)
         scanf("%d%d%d%d",&AP[i],&BP[i],&AS[i],&BS[i]);
}

int f[MAXN+1][MAXP+1];

int Ans = 0;
void Renew(int i, int j, int v){
     if (i > n)
        Ans = MAX(Ans, v);
     else
         f[i][j] = MAX(f[i][j], v);
}

class Queue{
      public:
             int head,tail,len;
             int v[MAXP+1];
             int p[MAXP+1];
             void clear(){
                  head = 1, tail = 0;
             }
             void set(int len){
                  this->len = len;
             }
             void push(int pos, int val){
                  if (head<=tail && abs(pos - p[head])-1 > len) head++;
                  while (head<=tail && v[tail] <= val) tail--;
                  p[++tail] = pos, v[tail] = val;
             }
             int front(int j){
                 while (head<tail && abs(j-p[head]) > len) head++;
                 return p[head];
             }
}q;
void Solve(){
     for (int i = 0; i<=n+W+1; i++)
         for (int j = 1; j<=MaxP; j++)
             f[i][j] = -INFINITE;
     for (int i = 1; i<=n; i++){
         for (int j = 1; j<=AS[i]; j++)
             f[i+W+1][j] = - AP[i] * j;
         for (int j = AS[i]+1; j<=MaxP; j++)
             f[i+W+1][j] = -INFINITE;
     }
     int asdf = 0;
     for (int i = 1; i<=n+W+1; i++){
         for (int j = 0; j<=MaxP; j++)
             f[i][j] = MAX(f[i][j], f[i-1][j]);
         int t;
         /**//*
            g[j] - AP * (i - j) > g[k] - AP * (i - k)
            g[j] + AP * j > g[k] + AP * k
            
            g[j] + BP * (j - i) > g[k] + BP * (j - i)
            g[j] + BP * j > g[k] + BP * j
          */
         if ((t = i-W-1) >= 1){
             // Buy
             q.clear(); q.set(AS[t]);
             q.push(0, f[t][0]);
             for (int j = 1; j<=MaxP; j++){
                 int tmp = q.front(j);
                 f[i][j] = MAX(f[i][j], f[t][tmp] - AP[t] * (j - tmp));
                 q.push(j, f[t][j] + AP[t] * j);
             }
             // Sell
             q.clear(); q.set(BS[t]);
             q.push(MaxP,f[t][MaxP] + BP[t] * MaxP);
             for (int j = MaxP-1; j>=0; j--){
                 int tmp = q.front(j);
                 f[i][j] = MAX(f[i][j], f[t][tmp] + BP[t] * (tmp - j));
                 q.push(j, f[t][j] + BP[t] * j);
             }
             for (int j = 0; j<=MaxP; j++)
                 Ans = MAX(Ans, f[i][j]);
         }
     }
     printf("%d\n",Ans);
}

int main(){
    Init();
    Solve();
    return 0;
}
