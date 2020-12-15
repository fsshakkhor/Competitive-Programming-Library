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
#define all(v) v.begin(),v.end()
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
const int N = 100005;
int L[N] , Pr[N] , P[N][22];

vector<int>G[N];

int st[N] , ed[N];
void dfs(int node,int pre,int dep)
{
    static int timer = 0;
    st[node] = ++timer;
    Pr[node] = pre;
    L[node] = dep;

    for(int i : G[node]){
        if(i==pre)continue;
        dfs(i,node,dep+1);
    }
    ed[node] = timer;
}
void init()
{
    for(int i = 0;i < N;i++)for(int j = 0;j<22;j++)P[i][j] = 1;
    FOR(i,1,N)P[i][0] = Pr[i];

    for(int j = 1;(1 << j)  <  N;j++){
        for(int i = 0;i < N;i++){
                P[i][j] = P[P[i][j-1]][j-1];
        }
    }
}
int query(int p,int q)
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
int isanc(int u, int v) {
    return (st[u]<=st[v]) && (ed[v]<=ed[u]);
}
int n , q;

//That will hold the auxilary tree
vector<int>Tree[N];

vector<int> build_auxiliary_tree(vector<int>&nodes){
    nodes.push_back(1);
    set<int>distinctNodes;
    //I am also taking the parents because I want to if my child is imp or not
    for(int i = 0;i < nodes.size();i++){
        distinctNodes.insert(nodes[i]);
        if(Pr[nodes[i]] > 0)distinctNodes.insert(Pr[nodes[i]]);
    }

    vector<int>v;
    for(int i : distinctNodes)v.push_back(i);

    sort(v.begin(),v.end(),[](int x,int y){
        return st[x] < st[y];
    });
    int sz = v.size();
    for(int i = 1;i < sz;i++){
        v.push_back(query(v[i - 1],v[i]));
    }
    SORT(v);
    v.erase(unique(all(v)),v.end());
    sort(v.begin(),v.end(),[](int x,int y){
        return st[x] < st[y];
    });
    stack<int>stk;
	stk.push(v[0]);
	for(int i=1;i < v.size();i++){
		while(!isanc(stk.top(),v[i])) stk.pop();
		Tree[stk.top()].pb(v[i]);
		stk.push(v[i]);
	}
    return v;
}
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cin >> n;
    FOR(i,1,n-1){
        int u , v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,1,0);
    init();

    cin >> q;
    for(int i = 1;i <= q;i++){
        int k;cin >> k;
        vector<int>nodes;
        for(int j = 1;j <= k;j++){
            int c;cin >> c;
            nodes.push_back(c);
        }
        vector<int>v = build_auxiliary_tree(nodes);


        for(int i : v)Tree[i].clear();
    }
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
