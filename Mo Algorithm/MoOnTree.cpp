#include<bits/stdc++.h>

using namespace std;

#define fRead(x)  freopen(x,"r",stdin)
#define fWrite(x) freopen (x,"w",stdout)

#define LL long long
#define ULL unsigned long long
#define ff first
#define ss second
#define pb push_back
#define INF 2e16
#define PI acos(-1.0)
#define mk make_pair
#define pii pair<int,int>
#define pll pair<LL,LL>


#define min3(a,b,c) min(a,min(b,c))
#define max3(a,b,c) max(a,max(b,c))
#define min4(a,b,c,d) min(a,min(b,min(c,d)))
#define max4(a,b,c,d) max(a,max(b,max(c,d)))
#define SQR(a) ((a)*(a))
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define REP(i,b) for(int i=0;i<b;i++)
#define MEM(a,x) memset(a,x,sizeof(a))
#define ABS(x) ((x)<0?-(x):(x))

#define scanI(a) scanf("%d",&a)
#define scanI2(a,b) scanI(a) , scanI(b)
#define scanI3(a,b,c) scanI(a), scanI(b), scanI(c)
#define scanI4(a,b,c,d) scanI(a), scanI(b), scanI(c), scanI(d)

#define scanL(a) scanf("%I64d",&a)
#define scanL2(a,b) scanL(a) , scanL(b)
#define scanL3(a,b,c) scanL(a), scanL(b), scanL(c)
#define scanL4(a,b,c,d) scanL(a), scanL(b), scanL(c), scanL(d)

#define SORT(v) sort(v.begin(),v.end())
#define REV(v) reverse(v.begin(),v.end())


#define FastRead ios_base::sync_with_stdio(0);cin.tie(nullptr);
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

#pragma GCC target ("avx2")
#pragma GCC optimization ("O2")
#pragma GCC optimization ("unroll-loops")
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

inline LL BigMod(LL B,LL P,LL M){LL R=1;while(P>0){if(P%2==1){R=(R*B)%M;}P/=2;B=(B*B)%M;}return R;}

struct data
{
    int l,r,id;
};
int n , q , sq;
bool cmp(data A,data B)
{
    if(A.l/sq!=B.l/sq)return A.l/sq < B.l/sq;
    return A.r<B.r;
}

const int N = 200005;
const LL MOD = 1e9 + 7;

int ara[N],newara[N];
vector<int>g[N];
int st[N],ed[N],Pr[N],P[N][18],L[N];

int timer = 0;
int vis[N],who[N];
void dfs(int node,int pre,int dep)
{
    st[node] = ++timer;
    who[timer] = node;
    newara[timer] = ara[node];
    L[node] = dep;
    Pr[node] = pre;

    for(int i : g[node]){
        if(i == pre)continue;
        dfs(i,node,dep + 1);
    }
    ed[node] = ++timer;
    who[timer] = node;
    newara[timer] = ara[node];
}
void init()
{
    for(int i = 0;i < N;i++)for(int j = 0;j<18;j++)P[i][j] = 1;
    FOR(i,1,N - 1)P[i][0] = Pr[i];

    for(int j = 1;(1 << j) < N;j++){
        for(int i = 0;i < N;i++){
            P[i][j] = P[P[i][j-1]][j-1];
        }
    }
}
int query(int p,int q)
{
    if(L[p] < L[q])swap(p,q);

    for(int i = 17;i>=0;i--){
        if(L[P[p][i]] >= L[q])p = P[p][i];
    }
    if(p == q)return p;
    for(int i = 17;i>=0;i--){
        if(P[p][i]!=P[q][i]){
            p = P[p][i]; q = P[q][i];
        }
    }
    return Pr[p];
}

data Q[N];
int lca[N];

const int M = 1000005;
bool stat[M];

int facP[M][8];
int facC[M][8];
int sz[M];

void siv()
{
    for(int i = 4;i < M;i += 2)stat[i] = 1;
    int sq = sqrt(M);
    for(int i = 3;i <= sq;i += 2){
        if(stat[i])continue;
        for(int j = i * i;j < M;j += 2 * i)stat[j] = 1;
    }
    for(int i = 2;i < M;i++){
        if(stat[i])continue;
        for(int j = i;j < M;j += i){
            int temp = j,cnt = 0;
            while(temp % i == 0){
                temp/=i;
                cnt++;
            }
            facP[j][sz[j]] = i;
            facC[j][sz[j]] = cnt;
            sz[j]++;
//            fac[j].push_back(mk(i,cnt));
        }
    }
}
const int F = 10 * N;
LL inv[F];

LL fcount[M];
LL ans;
inline void add(int val)
{
    for(int i = 0;i < sz[val];i++){
        ans = (ans * inv[(fcount[facP[val][i]] + 1)]) % MOD;
        fcount[facP[val][i]] += facC[val][i];
        ans = (ans * (fcount[facP[val][i]] + 1)) % MOD;
    }
//    for(int i = 0;i < fac[val].size();i++){
//        ans = (ans * inv[(fcount[fac[val][i].first] + 1)]) % MOD;
//        fcount[fac[val][i].first] += fac[val][i].second;
//        ans = (ans * (fcount[fac[val][i].first] + 1)) % MOD;
//    }
}
inline void remove(int val)
{
    for(int i = 0;i < sz[val];i++){
        ans = (ans * inv[(fcount[facP[val][i]] + 1)]) % MOD;
        fcount[facP[val][i]] -= facC[val][i];
        ans = (ans * (fcount[facP[val][i]] + 1)) % MOD;
    }
//    for(int i = 0;i < fac[val].size();i++){
//        ans = (ans * inv[(fcount[fac[val][i].first] + 1)]) % MOD;
//        fcount[fac[val][i].first] -= fac[val][i].second;
//        ans = (ans * (fcount[fac[val][i].first] + 1)) % MOD;
//    }
}
inline void modify(int index)
{
    int node = who[index];

    if(vis[node] == 0)add(newara[index]);
    else remove(newara[index]);

    vis[node] = 1 - vis[node];
}

LL answer[N];
int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    siv();
    for(int i = 1;i < F;i++)inv[i] = BigMod(i,MOD-2,MOD);

    int t;
    scanf("%d",&t);

    while(t--){
        timer = 0;
        ans = 1;
        MEM(fcount,0);
        MEM(lca,0);
        MEM(vis,0);

        for(int i = 0;i < N;i++)g[i].clear();

        scanf("%d",&n);
        sq = sqrt(n * 15) + 11;

        for(int i = 1;i < n;i++){
            int a , b;
            scanf("%d %d",&a,&b);
            g[a].pb(b);
            g[b].pb(a);
        }
        for(int i = 1;i <= n;i++)scanf("%d",&ara[i]);
        dfs(1,1,0);
        init();
//        for(int i = 1;i <= 2 * n;i++)cout << newara[i] << " ";cout << endl;
//        for(int i = 1;i <= 2 * n;i++)cout << who[i] << " ";cout << endl;
        scanf("%d",&q);
        for(int i = 1;i <= q;i++){
            int u , v;
            scanf("%d %d",&u,&v);
            if(st[u] > st[v])swap(u,v);
            int ancestor = query(u,v);

            if(ancestor == u)Q[i].l = st[u] , Q[i].r = st[v] ,Q[i].id = i;
            else Q[i].l = ed[u] , Q[i].r = st[v], Q[i].id = i , lca[i] = ancestor;

        }
        sort(Q + 1,Q + q + 1,cmp);

        int mol = 1;
        int mor = 0;
        for(int i = 1;i<=q;i++){
            int l = Q[i].l;
            int r = Q[i].r;

            while(mor < r){
                mor++;
                int node = who[mor];

                if(vis[node] == 0)add(newara[mor]);
                else remove(newara[mor]);

                vis[node] = 1 - vis[node];

            }
            while(mor > r){
                int node = who[mor];

                if(vis[node] == 0)add(newara[mor]);
                else remove(newara[mor]);

                vis[node] = 1 - vis[node];
                mor--;
            }
            while(mol < l){
                int node = who[mol];

                if(vis[node] == 0)add(newara[mol]);
                else remove(newara[mol]);

                vis[node] = 1 - vis[node];
                mol++;
            }

            while(mol>l){
                mol--;
                int node = who[mol];

                if(vis[node] == 0)add(newara[mol]);
                else remove(newara[mol]);

                vis[node] = 1 - vis[node];
            }

            if(lca[Q[i].id]){
                add(newara[st[lca[Q[i].id ]]]);
                answer[Q[i].id] = ans;
                remove(newara[st[lca[Q[i].id ]]]);
            }else{
                answer[Q[i].id] = ans;
            }
        }
        for(int i = 1;i <= q;i++)printf("%lld\n",answer[i]);
    }
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
