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

#define __int128        long long
const LL is_query = -(1LL<<62);
struct Line {
    LL m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        LL x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
    bool isEmpty = true;
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;

        return (__int128) (x->b - y->b) * (z->m - y->m) >= (__int128)(y->b - z->b) * (y->m - x->m);
    }
    void insert_line(LL m, LL b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
        isEmpty = false;
    }
    LL eval(LL x) {
        if(isEmpty) return -1e18;
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};

const int N = 300005;
LL P[N],A[N],H[N];
int n;

LL dp[N];
HullDynamic Tree[N];


void update(int idx,LL m,LL b)
{
    while(idx < N){
        Tree[idx].insert_line(m,b);
        idx += (idx&-idx);
    }
}
LL query(int idx,LL x)
{
    LL ret = -1e18;
    while(idx > 0){
        if(!Tree[idx].empty()){
            LL val = Tree[idx].eval(x);
            debug(idx,val);
            ret = max(ret,val);
        }
        idx -= (idx & -idx);
    }
    return ret;
}
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cin >> n;
    FOR(i,1,n)cin >> P[i];
    FOR(i,1,n)cin >> A[i];
    FOR(i,1,n)cin >> H[i];


    dp[1] = -A[1];
    update(P[1],2 * H[1],dp[1] - SQR(H[1]));
    dp[1] -= SQR(H[1]);


    for(int pos = 2;pos <= n;pos++){
        dp[pos] = query(P[pos] - 1,H[pos]);

        dp[pos] -= SQR(H[pos]);
        dp[pos] -= A[pos];

        LL m = 2 * H[pos];
        LL b = dp[pos] - SQR(H[pos]);

        update(P[pos],m,b);
//        for(int i = 1;i < pos;i++){
//            if(P[i] < P[pos]){
//                dp[pos] = max(dp[pos],dp[i] - (SQR(H[pos] - H[i]) + A[pos]));
//            }
//        }
        /*
            += H[pos]^2
            m = 2 * H[i] * H[pos]
            c = -H[i] ^ 2 + dp[i]
        */
    }
    cout << -dp[n] << "\n";
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}

//
