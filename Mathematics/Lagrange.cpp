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

LL BigMod(LL b,LL p,LL m)
{
    LL ret = 1;
    while(p > 0){
        if(p % 2 == 1)ret = (ret * b) % m;
        p = p >> 1;
        b = (b * b) % m;
    }
    return ret;
}
const LL MOD = 1e9 + 7;
LL Lagrange(vector<LL>p,LL x)
{
    int n = p.size();
    if(x < n) return p[x];
    LL k = 1;
    for(int i = 1; i < n; ++i) k = (k * (x - i)) % MOD, k = (k * BigMod(MOD - i,MOD - 2,MOD)) % MOD;
    LL ans = (p[0] * k) % MOD;
    for(int i = 1; i < n; ++i) {
        k = (k * (x - i + 1)) % MOD ;
        k = (k * BigMod(((x - i) * i) % MOD,MOD - 2,MOD)) % MOD;
        k = (k * (i - n)) % MOD;
        ans = (ans + k * p[i]) % MOD;
    }
    return ans;
}
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    FastRead
    int n, k;
    cin >> n >> k;
    vector<LL> p;
    LL sum = 0;
    p.push_back(0);
    for (int i = 1; i <= k + 1; i++) {
    	sum = (sum + BigMod(i,k,MOD)) % MOD;
    	p.push_back(sum);
    }
    LL ans = Lagrange(p, n);
    ans = (ans + MOD) % MOD;
    cout << ans << '\n';
    return 0;
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
