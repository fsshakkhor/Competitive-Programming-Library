#include<bits/stdc++.h>

using namespace std;

#define fRead(x)        freopen(x,"r",stdin)
#define fWrite(x)       freopen (x,"w",stdout)

#define LL              long long
#define ULL             unsigned long long
#define ff              first
#define ss              second
#define pb              push_back
#define INF             1e9
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

#define MAX 10005
vector<int> G[MAX];
set<int> g[MAX];

vector<pair<int, int> > bridges;
int low[MAX], vis[MAX], artPoint[MAX], visTime, noc;

void articulationPointAndBridge(int u, int par=-1){
	low[u]=vis[u]=++visTime;
	for(int j=0; j<(int)G[u].size(); j++){
		int v=G[u][j];
		if(v==par) continue; /// back-edge to direct parent
		if(!vis[v]){ /// A tree edge
			articulationPointAndBridge(v, u);
			if(low[v]>=vis[u]) artPoint[u]=true; /// Can't reach back to it's anchestor
			if(low[v]>vis[u]) bridges.push_back({u, v}); /// Can't reach back to u or it's anchestor
			low[u]=min(low[u], low[v]);
			if(par==-1) noc++;
		}
		else low[u]=min(low[u], vis[v]); /// A back-edge
	}
}

void processAPB(int n){ /// 0 indexed
	for(int i=0; i<n; i++) low[i]=vis[i]=artPoint[i]=0; visTime=0;
	bridges.clear();
	for(int i=0; i<n; i++){
		if(!vis[i]){
			noc=0; articulationPointAndBridge(i);
			artPoint[i]=(noc>1); /// special case, noc(number of components of root node)
		}
	}
}

int id,reg[MAX];
map<int,int>mp[MAX];

void dfs(int node)
{
    reg[node] = id;
    for(int i = 0;i < G[node].size();i++){
        int go = G[node][i];
        if(mp[node][go] == 1 or reg[go] > 0)continue;
        dfs(go);
    }
}
int deg[MAX];
int main()
{

    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int t,cases = 0;
    cin >> t;
    while(t--){
        int n , m;
        cin >> n >> m;
        for(int i = 0;i <= n;i++)G[i].clear(),g[i].clear(),mp[i].clear();
        id = 0;MEM(reg,0);MEM(deg,0);

        for(int i = 1;i <= m;i++){
            int a , b;
            cin >> a >> b;
            G[a].pb(b);
            G[b].pb(a);
        }
        processAPB(n);

        for(int i = 0;i < bridges.size();i++){
            mp[bridges[i].ff][bridges[i].ss] = 1;
            mp[bridges[i].ss][bridges[i].ff] = 1;
        }
        for(int i = 0;i < n;i++){
            if(reg[i] == 0)id++,dfs(i);
        }

        for(int i = 0;i < n;i++){
            for(int j : G[i]){
                int u = reg[i];
                int v = reg[j];
                if(u == v)continue;
                g[u].insert(v);
            }
        }
        for(int i = 1;i <= id;i++){
            for(int j : g[i]){
                deg[j]++;
            }
        }
        int ans = 0;
        for(int i = 1;i <= id;i++)if(deg[i] == 1)ans++;
        cout << "Case " << ++cases << ": " << (ans + 1)/2 << "\n";
    }

    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
