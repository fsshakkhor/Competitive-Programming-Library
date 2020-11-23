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
const int M=2005;

struct Edge{int v;Edge* n;};

typedef Edge* edge;

Edge pool[M*M*2];

edge top=pool,adj[M];

int V,E,Match[M],qh,qt,q[M],Father[M],base[M];

bool inq[M],inb[M];

void init()
{
     top=pool;
     memset(adj,0,sizeof(adj));
}

void addEdge(int u,int v)
{
  top->v=v,top->n=adj[u],adj[u]=top++;
  top->v=u,top->n=adj[v],adj[v]=top++;
}

int lowestCommonAncestor(int root,int u,int v)
{
  static bool inp[M];
  memset(inp,0,sizeof(inp));
  while(1)
    {
      inp[u=base[u]]=true;
      if (u==root) break;
      u=Father[Match[u]];
    }
  while(1)
    {
      if (inp[v=base[v]]) return v;
      else v=Father[Match[v]];
    }
}

void mark_blossom(int lca,int u)
{
  while (base[u]!=lca)
    {
      int v=Match[u];
      inb[base[u]]=inb[base[v]]=true;
      u=Father[v];
      if (base[u]!=lca) Father[u]=v;
    }
}

void blossom_contraction(int s,int u,int v)
{
  int lca=lowestCommonAncestor(s,u,v);
  memset(inb,0,sizeof(inb));
  mark_blossom(lca,u);
  mark_blossom(lca,v);
  if (base[u]!=lca)
    Father[u]=v;
  if (base[v]!=lca)
    Father[v]=u;
  for (int u=0;u<V;u++)
    if (inb[base[u]])
      {
	base[u]=lca;
	if (!inq[u])
	  inq[q[++qt]=u]=true;
      }
}

int find_augmenting_path(int s)
{
  memset(inq,0,sizeof(inq));
  memset(Father,-1,sizeof(Father));
  for (int i=0;i<V;i++) base[i]=i;
  inq[q[qh=qt=0]=s]=true;
  while (qh<=qt)
    {
      int u=q[qh++];
      for (edge e=adj[u];e;e=e->n)
        {
	  int v=e->v;
	  if (base[u]!=base[v]&&Match[u]!=v)
	    if ((v==s)||(Match[v]!=-1 && Father[Match[v]]!=-1))
	      blossom_contraction(s,u,v);
	    else if (Father[v]==-1)
	      {
		Father[v]=u;
		if (Match[v]==-1)
		  return v;
		else if (!inq[Match[v]])
		  inq[q[++qt]=Match[v]]=true;
	      }
        }
    }
  return -1;
}

int AugmentedPath(int source,int sink)
{
  int u=sink,v,w;
  while (u!=-1)
    {
      v=Father[u];
      w=Match[v];
      Match[v]=u;
      Match[u]=v;
      u=w;
    }
  return sink!=-1;
}
int blossoms()
{
  int matchc=0;
  int F = 0;
  memset(Match,-1,sizeof(Match));
  for (int u=0;u<V;u++)
    if (Match[u]==-1)
      matchc+=AugmentedPath(u,find_augmenting_path(u));
  return matchc;
}

const int N = 3005;
const int bits = 3000;
int n , m;
bitset<bits>bit[N];

int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int t;
    cin >> t;
    while(t--){
        init();
        cin >> n >> m;
        for(int i = 0;i < n;i++)bit[i].reset();
        vector<pii>edge;
        for(int i = 0;i < m;i++){
            int x , y;
            cin >> x >> y;
            x--;y--;
            bit[x][y] = 1;
            bit[y][x] = 1;
            if(x > y)swap(x,y);
            edge.push_back(mk(x,y));
        }
        set<pair<pii,int> >SET;
        vector<pair<pii,int> >vec;
        for(int i = 0;i < edge.size();i++){
            int x = edge[i].ff;
            int y = edge[i].ss;
            bitset<bits> v = bit[x] & bit[y];
            int ptr = -1;
            while(v._Find_next(ptr) != bits){
                ptr = v._Find_next(ptr);
                vector<int>temp;
                temp.push_back(x);temp.push_back(y);temp.push_back(ptr);
                SORT(temp);
                SET.insert(mk(mk(temp[0],temp[1]),temp[2]));
            }
        }

        for(auto x : SET)vec.push_back(x);

        V = vec.size();

        for(int i = 0;i < vec.size();i++){

            map<int,int>mp;
            mp[vec[i].ff.ff] = 1;
            mp[vec[i].ff.ss] = 1;
            mp[vec[i].ss] = 1;
            for(int j = i + 1;j < vec.size();j++){
                if(mp[vec[j].ff.ff] || mp[vec[j].ff.ss] || mp[vec[j].ss]){
                    addEdge(i,j);
                }
            }
        }

        int ans = blossoms();
        cout << V - ans << "\n";

    }
    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}
