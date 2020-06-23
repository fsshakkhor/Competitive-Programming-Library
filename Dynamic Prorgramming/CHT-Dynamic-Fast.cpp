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
//#pragma GCC optimization ("O2")
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

bool Q;
struct Line {
	mutable LL m, c, p;
	bool operator<(const Line& o) const {
		return Q ? p < o.p : m < o.m;
	}
};

const LL inf = LLONG_MAX;

struct LineContainer : multiset<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	LL div(LL a, LL b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->m == y->m) x->p = x->c > y->c ? inf : -inf;
		else x->p = div(y->c - x->c, x->m - y->m);
		return x->p >= y->p;
	}
	void addLine(LL m, LL c) {
		auto z = insert({m, c, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	LL query(LL x) {
	    if(empty()) return 0;
		Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
		return l.m * x + l.c;
	}
	bool isEmpty(){ return (empty()) ; }
	void Clear()
	{
	    clear() ;
	}
}cht;


const int N = 1000005;
struct Data{
    int x , y;
    LL a;
}ara[N];

int n;
LL dp[N];
bool cmp(Data &a,Data &b){
    return a.x < b.x;
}
int32_t main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    FastRead
    cin >> n;
    FOR(i,1,n){
        cin >> ara[i].x >> ara[i].y >> ara[i].a;
    }
    sort(ara + 1,ara + n + 1,[](Data &a,Data &b){
        if(a.x == b.x)return a.a < b.a;
        return a.x < b.x;
    });
    cht.addLine(0,0);
    LL ans = 0;
    for(int pos = 1;pos <= n;pos++){
        LL val = cht.query(ara[pos].y);
        dp[pos] = val + (LL)ara[pos].x * (LL)ara[pos].y - ara[pos].a;
        cht.addLine(-ara[pos].x,dp[pos]);
        ans = max(ans,dp[pos]);
    }

    cout << ans << "\n";
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
