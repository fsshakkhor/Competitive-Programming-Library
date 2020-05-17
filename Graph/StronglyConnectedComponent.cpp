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
#pragma GCC optimization ("O3")
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

const int N = 1005;
vector<int>G[N],rG[N];
stack<int>st;
bool vis[N];
int comp_id[N];
int n , m;

void top(int node)
{
    if(vis[node])return;
    vis[node] = 1;
    for(int i : G[node]){
        top(i);
    }
    st.push(node);
}

int comp_num;
void dfs(int node)
{
    if(vis[node])return;
    vis[node] = 1;
    comp_id[node] = comp_num;
    for(int i : rG[node]){
        dfs(i);
    }
}
set<int>g[N];

int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int t,cases = 0;
    scanf("%d",&t);

    while(t--){
        comp_num = 0;

        scanf("%d %d",&n,&m);
        FOR(i,1,n)G[i].clear() , rG[i].clear(),g[i].clear();
        FOR(i,1,m)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            G[a].pb(b);
            rG[b].pb(a);
        }
        MEM(vis,0);
        int cnt = 0;
        for(int i = 1;i <= n;i++){
            if(vis[i] == 0)top(i);
        }
        MEM(vis,0);
        while(!st.empty()){
            int node = st.top();
            st.pop();
            if(vis[node])continue;
            comp_num++;
            dfs(node);
        }
        for(int i = 1;i <= n;i++){
            for(int j : G[i]){
                if(comp_id[i] == comp_id[j])continue;
                debug(comp_id[i],comp_id[j]);
                g[comp_id[i]].insert(comp_id[j]);
            }
        }
    }
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
