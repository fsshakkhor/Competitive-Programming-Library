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
 
const int N = 300005;
int n , p[N] , q[N] , pos[N];
int tree[4 * N],lazy[4 * N];
 
void upd(int node,int val){
    lazy[node] += val;
    tree[node] += val;
}
void push(int node){
    if(lazy[node] != 0){
        upd(2 * node,lazy[node]);
        upd(2 * node + 1,lazy[node]);
        lazy[node] = 0;
    }
}
void update(int node,int L,int R,int l,int r,int v){
    if(R < l or r < L)return;
    if(L >= l and R <= r){
        upd(node,v);
        return;
    }
    int mid = (L + R) >> 1;
    push(node);
    update(2 * node,L,mid,l,r,v);
    update(2 * node + 1,mid + 1,R,l,r,v);
    tree[node] = min(tree[node * 2],tree[node * 2 + 1]);
}
 
int ispossible(int val){
    update(1,1,n,1,pos[val],-1);
    if(tree[1] >= 0)return true;
    update(1,1,n,1,pos[val],1);
    return false;
}
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cin >> n;
    FOR(i,1,n)cin >> p[i] , pos[p[i]] = i;
    FOR(i,1,n)cin >> q[i];
 
    int ans = n;
 
    for(int i = 1;i <= n;i++){
        while(ispossible(ans))ans--;
        cout << ans << " ";
        update(1,1,n,1,q[i],1);
    }
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
