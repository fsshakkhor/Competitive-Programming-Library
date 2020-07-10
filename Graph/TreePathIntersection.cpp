#include<bits/stdc++.h>
 
using namespace std;
 
#define fRead(x)        freopen(x,"r",stdin)
#define fWrite(x)       freopen (x,"w",stdout)
 
#define LL              long long
#define ULL             unsigned long long
#define ff              first
#define ss              second
#define pb              push_back
#define PI              acos(-1.0)
#define mk              make_pair
#define pii             pair<int,int>
#define pll             pair<LL,LL>
 
 
#define min3(a,b,c)     min(a,min(b,c))
#define max3(a,b,c)     max(a,max(b,c))
#define min4(a,b,c,d)   min(a,min(b,min(c,d)))
#define max4(a,b,c,d)   max(a,max(b,max(c,d)))
#define SQR(a)          ((a)*(a))
#define FOR(i,a,b)      for(int i=a;i<=b;i++)
#define ROF(i,a,b)      for(int i=a;i>=b;i--)
#define REP(i,b)        for(int i=0;i<b;i++)
#define MEM(a,x)        memset(a,x,sizeof(a))
#define ABS(x)          ((x)<0?-(x):(x))
 
#define SORT(v)         sort(v.begin(),v.end())
#define REV(v)          reverse(v.begin(),v.end())
#pragma GCC target ("avx2")
#pragma GCC optimization ("O2")
#pragma GCC optimization ("unroll-loops")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FastRead        ios_base::sync_with_stdio(0);cin.tie(nullptr);
 
const int N = 100000;
 
int L[N+5];
int Pr[N+5];
int P[N+5][22];
vector<int>G[N];
 
void dfs(int node,int pre,int dep)
{
    Pr[node] = pre;
    L[node] = dep;
 
    for(int i : G[node]){
        if(i==pre)continue;
        dfs(i,node,dep+1);
    }
}
void init()
{
    for(int i = 0;i<=N;i++)for(int j = 0;j<22;j++)P[i][j] = 1;
    FOR(i,1,N)P[i][0] = Pr[i];
 
    for(int j = 1;(1 << j) <= N;j++){
        for(int i = 0;i<=N;i++){
                P[i][j] = P[P[i][j-1]][j-1];
        }
    }
}
int LCA(int p,int q)
{
    if(L[p] < L[q])swap(p,q);
 
    for(int i = 21;i>=0;i--){
        if(L[P[p][i]] >= L[q])p = P[p][i];
    }
    if(p == q)return p;
    for(int i = 21;i>=0;i--){
        if(P[p][i]!=P[q][i]){
            p = P[p][i]; q = P[q][i];
        }
    }
    return Pr[p];
}
bool cmp(int u, int v){
    return L[u]>L[v];
}
void intersection(int &a, int &b, int &c, int &d){
    vector<int>comp;
 
    comp.push_back(LCA(a,c));
    comp.push_back(LCA(a,d));
    comp.push_back(LCA(b,c));
    comp.push_back(LCA(b,d));
    sort(comp.begin(), comp.end(), cmp);
    int path1= LCA(a,b) , path2=LCA(c,d), mara3;
 
    if(comp[0]==comp[1]){
        if(L[path1]<L[path2]) mara3=path2;
        else mara3=path1;
        if(comp[0]!=mara3){
            a=-1,b=-1;
            return;
        }
    }
 
    a=comp[0], b=comp[1];
}
 
int n , q;
int32_t main()
{
    cin >> n >> q;
    for(int i = 1;i < n;i++){
        int u , v;
        cin >> u >> v;
        G[u].pb(v);
        G[v].pb(u);
    }
    dfs(1,1,0);
    init();
 
    while(q--){
        int a , b , c ,d;
        cin >> a >> b >> c >> d;
        intersection(a,b,c,d);
        if(a == -1 and b == -1)cout << 0 << "\n";
        else{
            int ans = L[a] + L[b] - 2 * L[LCA(a,b)];
            cout << ans + 1 << "\n";
        }
 
    }
}
