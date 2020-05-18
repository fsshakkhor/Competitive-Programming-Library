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
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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

#define MAX 1008
namespace scc{
    int num[MAX], low[MAX], col[MAX], cycle[MAX], st[MAX];
    int tail, visTime, cc, K;
    //K is the number of components in SCC
    vector<int> G[MAX], S[MAX];

    void clear () {
        cc += 3;
        for(int i=0; i<MAX; i++) G[i].clear(), S[i].clear();
        tail = 0, K=0;
    }
    void tarjan ( int s ) {
        num[s] = low[s] = ++visTime;
        col[s] = cc + 1;
        st[tail++] = s;
        for(int i=0; i<int(G[s].size()); i++){
            int t = G[s][i];
            if ( col[t] <= cc ) {
                tarjan ( t );
                low[s]=min(low[s],low[t]);
            }
            /*Back edge*/
            else if (col[t]==cc+1)
                low[s]=min(low[s],low[t]);
        }
        if ( low[s] == num[s] ) {
            while ( 1 ) {
                int temp=st[tail-1];
                tail--;
                col[temp] = cc + 2;
                cycle[temp] = K; // set new root
                if ( s == temp ) break;
            }
            K++;
        }
    }
    void shrink( int n ) {
        for(int i=0; i<n; i++){
            int u=cycle[i];
            for(int j=0; j<int(G[i].size()); j++){
                int v=cycle[G[i][j]];
                if(u!=v) S[u].push_back(v);
            }
        }
        for(int i=0; i<K; i++){ ///Not always necessary
            sort ( S[i].begin(), S[i].end() );
            S[i].erase(unique(S[i].begin(), S[i].end()), S[i].end());
        }
    }

    void findSCC( int n) {
        for(int i=0; i<n; i++){
            if ( col[i] <= cc ) {
                tarjan ( i );
            }
        }
        shrink(n);
    }
};
namespace bpm{
    vector<int> G[MAX];
    int L[MAX], R[MAX];
    bool visited[MAX];

    void clear(){
        FOR(i, 0, MAX - 1) G[i].clear();
    }

    bool bipartite_matching(int u){
        for(auto &v: G[u]){
            if(visited[v]) continue;
            visited[v] = true;
            if(R[v]==-1 or bipartite_matching(R[v])){
                L[u] = v;
                R[v] = u;
                return true;
            }
        }
        return false;
    }

    int max_matching(int n){
        MEM(L,-1);MEM(R,-1);
        int tot = 0;
        for(int i = 0; i < n; i++){
            MEM(visited, 0);
            if(bipartite_matching(i)) tot++;
        }
        return tot;
    }
};

bool vis[MAX];

void dfs(int u, int root){
    vis[u] = 1;
    for(auto &v: scc::S[u]){
        if(vis[v]) continue;
        bpm::G[root].pb(v);
        dfs(v, root);
    }
}

void transitiveClosure(){
    for(int i = 0; i < scc::K; i++){
        MEM(vis, 0);
        dfs(i, i);
    }
}


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
        scc::clear();
        bpm::clear();
        int n , m;
        scanf("%d %d",&n,&m);
        for(int i = 0;i < m;i++){
            int u , v;
            scanf("%d %d",&u,&v);
            u--;v--;
            scc::G[u].pb(v);
        }
        scc::findSCC(n);
        transitiveClosure();
        int ans = bpm::max_matching(scc::K);
        printf("Case %d: %d\n",++cases,scc::K - ans);


    }
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
