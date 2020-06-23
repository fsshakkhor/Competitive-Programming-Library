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


vector<LL> slope, cons;
int ptr = 0;
bool bad(int l1, int l2, int l3) {
    return 1.0 * (cons[l3] - cons[l1]) * (slope[l1] - slope[l2])  < 1.0 * (cons[l2] - cons[l1]) * (slope[l1] - slope[l3]);
}
void add(LL _m, LL _b) {
    slope.push_back(_m);
    cons.push_back(_b);
    int s = slope.size();
    while(s >= 3 && bad(s-3, s-2, s-1)) {
        s--;
        slope.erase(slope.end()-2);
        cons.erase(cons.end()-2);
    }
}
LL f(int i, LL x) { return slope[i]*x + cons[i]; }
LL query(LL x) {
    if(ptr >= slope.size())
        ptr = slope.size()-1;
    while(ptr < slope.size()-1 &&
        f(ptr+1, x) < f(ptr, x))
        ptr++;
    return f(ptr, x);
}

const int N = 50005;
const int M = 1000005;

LL dp[N];
vector<pll>ara;
vector<LL>g[M];
LL n;
///In the expression variables with 'i' will be my X. 
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    cin >> n;
    for(LL i = 1;i <= n;i++){
        LL X , Y;
        cin >> X >> Y;
        g[X].push_back(Y);
    }

    LL mx = 0;
    for(LL i = M - 1;i >= 0;i--){
        if(g[i].empty())continue;
        SORT(g[i]);
        if(g[i].back() > mx)ara.push_back(mk(i,g[i].back()));
        mx = max(mx,g[i].back());
    }
    for(LL i = 1;i <= n;i++)dp[i] = 1e18;
    LL pre = 0;

    ///Using CHT

    for(LL i = 0;i < ara.size();i++){
        add(ara[i].first,pre);
        dp[i] = query(ara[i].second);
        pre = dp[i];
    }
    cout << dp[ara.size() - 1] << "\n";
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
//https://vjudge.net/contest/370406#problem/F
