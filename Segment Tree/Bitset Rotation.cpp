//https://codeforces.com/problemset/problem/633/G
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

int n , m , q , ara[N] , newara[N];
vector<int>g[N];

bitset<1000>Tree[4 * N] , primes;
int lazy[4 * N];

void build(int node,int L,int R){
    if(L == R){
        Tree[node][newara[L]] = 1;
        return;
    }
    int mid = (L + R) >> 1;
    build(node * 2,L,mid);
    build(node * 2 + 1,mid + 1,R);
    Tree[node] = (Tree[node * 2] | Tree[node * 2 + 1]);
}

void push(int node,int L,int R){
    bitset<1000>sft = Tree[node] >> (m - lazy[node]);
    Tree[node] = sft | (Tree[node] << lazy[node]);

    if(L != R){
        lazy[node * 2] = (lazy[node] + lazy[node * 2]) % m;
        lazy[node * 2 + 1] = (lazy[node] + lazy[node * 2 + 1]) % m;
    }
    lazy[node] = 0;
}

void update(int node,int L,int R,int l,int r,int sft){
    push(node,L,R);
    if(R < l or r < L)return;
    if(L >= l and R <= r){
        lazy[node] = sft;
        push(node,L,R);
        return;
    }
    int mid = (L + R) >> 1;
    update(2 * node,L,mid,l,r,sft);
    update(2 * node + 1,mid + 1,R,l,r,sft);
    Tree[node] = (Tree[node * 2] | Tree[node * 2 + 1]);
}

bitset<1000>query(int node,int L,int R,int l,int r){
    push(node,L,R);
    if(R < l or r < L)return bitset<1000>();
    if(L >= l and R <= r)return Tree[node];
    int mid = (L + R) >> 1;
    return query(2 * node,L,mid,l,r) | query(2 * node + 1,mid + 1,R,l,r);
}

int st[N] , ed[N];
int timer = 0;

void dfs(int node,int pre){
    st[node] = ++timer;
    newara[timer] = ara[node];

    for(int i : g[node]){
        if(i == pre)continue;
        dfs(i,node);
    }
    ed[node] = timer;
}
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    FastRead
    cin >> n >> m;
	for (int i=2;i<m;i++) {
		bool ok = 1;
		for (int j=2;j*j<=i;j++) {
			if (i%j==0) ok = 0;
		}
		primes[i] = ok;
	}

    FOR(i,1,n){
        cin >> ara[i];
        ara[i] %= m;
    }
    FOR(i,1,n-1){
        int u , v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,1);
    build(1,1,n);

    cin >> q;
    FOR(i,1,q){
        int tp;
        cin >> tp;
        if(tp == 1){
            int v , x;
            cin >> v >> x;
            update(1,1,n,st[v],ed[v],x % m);
        }else{
            int v;cin >> v;
            bitset<1000>B = query(1,1,n,st[v],ed[v]);
            cout << (B & primes).count() << "\n";
        }
    }
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
