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
#ifdef VAMP
     #define debug(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template < typename Arg1 >
    void __f(const char* name, Arg1&& arg1){
        cout << name << " = " << arg1 << std::endl;
    }
    template < typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names+1, ',');
        cout.write(names, comma - names) << " = " << arg1 <<" | ";
        __f(comma+1, args...);
    }
#else
    #define debug(...)
#endif


/*
Time Complexity: O(M * log N)
Link: https://www.youtube.com/watch?v=nMabN7SrHIU&feature=youtu.be
*/
const int N = 100005;
int n , m;

struct edge{
    int u , v , cost;
};

int pr[N],min_edge[N];
edge g[N];

int find(int r)
{
    if(pr[r] == r)return r;
    else return pr[r] = find(pr[r]);
}
bool merge(int u,int v)
{
    u = find(u);
    v = find(v);
    if(u == v)return 0;
    pr[v] = u;
    return 1;
}
void boruvka()
{
    int cnt_cmp = n;
    LL ans = 0;
    while(cnt_cmp > 1){
        for(int i = 1;i <= n;i++)min_edge[i] = -1;

        for(int i = 1;i <= m;i++){
            int u = find(g[i].u);
            int v = find(g[i].v);
            if(u == v)continue;

            if(min_edge[v]  == -1 || g[i].cost < g[min_edge[v]].cost){
                min_edge[v] = i;
            }
            if(min_edge[u]  == -1 || g[i].cost < g[min_edge[u]].cost){
                min_edge[u] = i;
            }
        }
        for(int i = 1;i <= n;i++){
            if(min_edge[i] != -1 and merge(g[min_edge[i]].u,g[min_edge[i]].v)){
                ans += g[min_edge[i]].cost;
                cnt_cmp--;
            }
        }
    }
    cout << ans << "\n";
}
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("output.txt", "w", stdout);
        freopen("input.txt", "r", stdin);
    #endif
    cin >> n >> m;

    for(int i = 1;i <= m;i++){
        cin >> g[i].u >> g[i].v >> g[i].cost;
    }

    for(int i = 1;i <= n;i++)pr[i] = i;

    boruvka();

    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
