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

const int N = 1e5 + 10;

vector<int> g[N];
vector<int> t[N], rg[N], bucket[N];
int sdom[N], par[N], idom[N], dsu[N], label[N];
int id[N], rev[N], T;
int find_(int u, int x = 0)
{
	if(u == dsu[u]) return x ? -1 : u;
	int v = find_(dsu[u], x+1);
	if(v < 0)return u;
	if(sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
	dsu[u] = v;
	return x ? v : label[u];
}

void dfs(int u)
{
	T++; id[u] = T; rev[T] = u;
	label[T] = T; sdom[T] = T; dsu[T] = T;
	for(int i = 0; i < g[u].size(); i++){
		int w = g[u][i];
		if(!id[w]) dfs(w), par[id[w]] = id[u];
		rg[id[w]].push_back(id[u]);
	}
}

void build(int source, int n)
{
    dfs(source); n = T;
	for(int i = n; i >= 1; i--){
		for(int j = 0; j < rg[i].size(); j++) sdom[i] = min(sdom[i], sdom[find_(rg[i][j])]);
		if(i > 1) bucket[sdom[i]].push_back(i);
		for(int j = 0; j < bucket[i].size(); j++){
			int w = bucket[i][j];
			int v = find_(w);
			if(sdom[v] == sdom[w]) idom[w] = sdom[w];
			else idom[w] = v;
		}
		if(i > 1) dsu[i] = par[i];
	}
	for(int i = 2; i <= n; i++){
		if(idom[i] != sdom[i]) idom[i]=idom[idom[i]];
		t[rev[i]].push_back(rev[idom[i]]);
		t[rev[idom[i]]].push_back(rev[i]);
	}
}
int n , m;

int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cin >> n >> m;
    for(int i = 0;i < m;i++){
        int a , b;
        cin >> a >> b;
        g[a].pb(b);
    }
    build(1,n);

     #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
