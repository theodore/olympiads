#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXTREAPNODE 5000000
#define MAXLSTNODE 1000000
#define MAXN 50000
#define MAXNUM 1000000000
#define INFINIT 1000000000
using namespace std;


int a[MAXN+1];
class TreapNode{
    public:
        int v,lt,rt,p,size;
        void set(int v){
            this->v = v;
            lt = rt = 0;
            p = rand();
            size = 1;
        }
};
TreapNode treapnode[MAXTREAPNODE+1];
int pos = 0;
class Treap{
    private:
    int cnt,root;
    void RightRotate(int &x){
        int lc = treapnode[x].lt;
        treapnode[x].lt = treapnode[lc].rt;
        treapnode[lc].rt = x;
        x = lc;
    }
    void LeftRotate(int &x){
        int rc = treapnode[x].rt;
        treapnode[x].rt = treapnode[rc].lt;
        treapnode[rc].lt = x;
        x = rc;
    }
    void Renew(int x){
        if (!x) return;
        treapnode[x].size = treapnode[treapnode[x].lt].size+treapnode[treapnode[x].rt].size+1;
    }
    void Add(int &x,int v){
        if (!x) treapnode[x = (++pos)].set(v);
        else{
            if (v<=treapnode[x].v){
                Add(treapnode[x].lt,v);
                if (treapnode[treapnode[x].lt].p<treapnode[x].p)
                    RightRotate(x);
            }
            else if (v>treapnode[x].v){
                Add(treapnode[x].rt,v);
                if (treapnode[treapnode[x].rt].p<treapnode[x].p)
                    LeftRotate(x);
            }
            Renew(treapnode[x].lt),Renew(treapnode[x].rt),Renew(x);
        }
    }
    void dfs(int x){
        if (!x) return;
        dfs(treapnode[x].lt);
        printf("%d ",treapnode[x].v);
        dfs(treapnode[x].rt);
    }
    int Ask(int &x,int k){
        if (k<=treapnode[treapnode[x].lt].size) return Ask(treapnode[x].lt,k);
        if (k == treapnode[treapnode[x].lt].size+1) return treapnode[x].v;
        if (k>treapnode[treapnode[x].lt].size+1) return Ask(treapnode[x].rt,k-treapnode[treapnode[x].lt].size-1);
    }
    int Find(int &x,int v){
        if (v == treapnode[x].v) return treapnode[treapnode[x].lt].size+1;
        if (v<treapnode[x].v){
            return Find(treapnode[x].lt,v);
        }
        if (v>treapnode[x].v){
            return treapnode[treapnode[x].lt].size+1+Find(treapnode[x].rt,v);
        }
    }
    void Del(int &x,int v){
        if (v<treapnode[x].v) Del(treapnode[x].lt,v);
        else if (v>treapnode[x].v) Del(treapnode[x].rt,v);
        else{
            if (!treapnode[x].lt&&!treapnode[x].rt)
                x = 0;
            else if (treapnode[x].lt&&!treapnode[x].rt)
                x = treapnode[x].lt;
            else if (!treapnode[x].lt&&treapnode[x].rt)
                x = treapnode[x].rt;
            else if (treapnode[treapnode[x].lt].p<treapnode[treapnode[x].rt].p)
                RightRotate(x),Del(treapnode[x].rt,v);
            else 
                LeftRotate(x),Del(treapnode[x].lt,v);
        }
        Renew(treapnode[x].lt),Renew(treapnode[x].rt),Renew(x);
    }
    int GetSmaller(int x,int v){
        if (!x) return 0;
        if (treapnode[x].v<=v)
            return treapnode[treapnode[x].lt].size+1+GetSmaller(treapnode[x].rt,v);
        if (treapnode[x].v>v) return GetSmaller(treapnode[x].lt,v);
    }
    public:
    Treap(){cnt = root = 0;}
    void Add(int v){
        cnt++;
        Add(root,v);
    }
    void dfs(){
        dfs(root);
    }
    int Ask(int k){
        return Ask(root,k);
    }
    int Find(int v){
        return Find(root,v);
    }
    void Change(int v1,int v2){
        Del(v1);
        Add(v2);
    }
    void Del(int v){
        cnt--;
        Del(root,v);
    }
    void DelRank(int k){
        int v = Ask(k);
        Del(v);
    }
    int Amount(){return cnt;}
    void Clear(){cnt = root = 0;}
    int GetSmaller(int x){
        return GetSmaller(root,x);
    }
};
class LSTNode{
    public:
        int l,r,lt,rt;
        Treap T;
};
int tot = 0;
LSTNode lstnode[MAXLSTNODE+1];
class LST{
    private:
    int AskRank(int x,int l,int r,int v){
        if (lstnode[x].l>=l&&lstnode[x].r<=r)
            return lstnode[x].T.GetSmaller(v);
        else{
            int mid = (lstnode[x].l+lstnode[x].r)>>1;
            if (r<=mid) return AskRank(lstnode[x].lt,l,r,v);
            else if (l>mid) return AskRank(lstnode[x].rt,l,r,v);
            else
                return AskRank(lstnode[x].lt,l,r,v)+AskRank(lstnode[x].rt,l,r,v);
        }
    }
    void Modify(int x,int p,int v){
        lstnode[x].T.Change(a[p],v);
        if (lstnode[x].l == lstnode[x].r) return;
        int mid = (lstnode[x].l+lstnode[x].r)>>1;
        if (p<=mid) Modify(lstnode[x].lt,p,v);
        else if (p>mid) Modify(lstnode[x].rt,p,v);
        else{
            Modify(lstnode[x].lt,p,v);
            Modify(lstnode[x].rt,p,v);
        }
    }
    public:
    LST(){tot=0;pos = 0;}
    void BuildTree(int l,int r){
        int x = ++tot;
        lstnode[x].T.Clear();
    lstnode[x].l = l,lstnode[x].r = r;
        for (int i = l; i<=r; i++)
            lstnode[x].T.Add(a[i]);
        if (l == r) lstnode[x].lt = lstnode[x].rt = 0;
        else{
            int mid = (l+r)>>1;
            lstnode[x].lt = tot+1,BuildTree(l,mid);
            lstnode[x].rt = tot+1,BuildTree(mid+1,r);
        }
    }
    int Ask(int L,int R,int k){
        int l = 0,r = MAXNUM;
        while (l<=r){
            int mid = (l+r)>>1;
            int t1 = AskRank(1,L,R,mid);
            int t2 = AskRank(1,L,R,mid-1);
            if (k<=t1&&k>t2) return mid;
            if (t1<k) l = mid+1;
            else r = mid;
        }
    }
    void Modify(int p,int v){
        Modify(1,p,v);
        a[p] = v;
    }
    void Clear(){
        tot = 0;pos = 0;
    }
};
LST T;
void Solve(){
    T.Clear();
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i = 1; i<=n; i++)
        scanf("%d",&a[i]);
    T.BuildTree(1,n);
    for (int i = 1; i<=m; i++){
        char ch;
        int t1,t2,t3;
        scanf("%c",&ch);
        while (ch == '\n'||ch == ' ') scanf("%c",&ch);
        if (ch == 'Q'){
            scanf("%d%d%d",&t1,&t2,&t3);
            printf("%d\n",T.Ask(t1,t2,t3));
        }
        if (ch == 'C'){
            scanf("%d%d",&t1,&t2);
            T.Modify(t1,t2);
        }
    }
}
int main(){
    //freopen("2112.in","r",stdin);
    //freopen("2112.out","w",stdout);
    srand(1);
    int t;
    Solve();
    return 0;
}
