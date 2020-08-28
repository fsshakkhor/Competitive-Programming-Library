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
#pragma GCC optimization ("O2")
#pragma GCC optimization ("unroll-loops")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FastRead        ios_base::sync_with_stdio(0);cin.tie(nullptr);
#ifdef VAMP
#define debug(...) __f(#__VA_ARGS__, __VA_ARGS__)
template < typename Arg1 >
void __f(const char* name, Arg1&& arg1)
{
    cout << name << " = " << arg1 << std::endl;
}
template < typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args)
{
    const char* comma = strchr(names+1, ',');
    cout.write(names, comma - names) << " = " << arg1 <<" | ";
    __f(comma+1, args...);
}
#else
#define debug(...)
#endif

const int MAXN = 100005 << 1; /// 2 * maximum possible string size
const int MAXC = 26; /// Size of the character set

struct SF{
    int sz, last;
    int len[MAXN], link[MAXN], ed[MAXN][MAXC], cnt[MAXN];
    bool terminal[MAXN];
    vector <int> G[MAXN];

    void init() {
        MEM(ed[0],-1);
        len[0] = 0, link[0] = -1, sz = 1, last = 0, terminal[0] = false;
    }

    inline int scale(char c) { return c-'a'; }

    void extend(char c) {
        c = scale(c);
        int cur = sz++;

        terminal[cur] = false;
        cnt[cur] = 1;

        MEM(ed[cur],-1);

        len[cur] = len[last] + 1;
        int p = last;
        while (p != -1 && ed[p][c]==-1) {
            ed[p][c] = cur;
            p = link[p];
        }
        if (p == -1) link[cur] = 0;
        else {
            int q = ed[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int clone = sz++;
                len[clone] = len[p] + 1;
                memcpy(ed[clone],ed[q],sizeof(ed[q]));
                link[clone] = link[q];
                while (p != -1 && ed[p][c] == q) {
                    ed[p][c] = clone;
                    p = link[p];
                }
                link[q] = link[cur] = clone;

                cnt[clone] = 0;
                terminal[clone] = false;
            }
        }
        last = cur;
    }
    void dfs(int node){
        for(int i : G[node]){
            dfs(i);
            cnt[node] += cnt[i];
        }
    }
    void build(){
        for(int i=1;i<sz;i++) G[link[i]].pb(i);
        dfs(0);
        cnt[0] = 0;
    }

}sf;
int k , found;
string s;
void dfs(int node)
{
    found += sf.cnt[node];

    if(found >= k){
        cout << s << "\n";
        exit(0);
    }
    for(int i = 0;i < 26;i++){

        if(sf.ed[node][i] != -1){
            s += char(i + 'a');
            dfs(sf.ed[node][i]);
            s.pop_back();
        }
    }
}
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    sf.init();
    FastRead
    string str;cin >> str;
    cin >> k;

    for(int i = 0;i < str.size();i++){
        sf.extend(str[i]);
    }
    sf.build();
    dfs(0);
    cout << "No such line.";
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
