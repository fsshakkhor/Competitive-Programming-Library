#include<bits/stdc++.h>

using namespace std;

#define fRead(x)        freopen(x,"r",stdin)
#define fWrite(x)       freopen (x,"w",stdout)

#define LL              long long
#define ULL             unsigned long long
#define ff              first
#define ss              second
#define pb              push_back
#define INF             2e16
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

#define FastRead        ios_base::sync_with_stdio(0);cin.tie(nullptr);



const int LOG = 20;

struct AC
{
    int N, P;
    vector<vector<int>> next;
    vector<int> link, out_link ,counter, leaf;
    vector<vector<int>> out;
    vector<string>dictionary;
    AC(): N(0), P(0)
    {
        node();
    }

    void clear()
    {
        next.clear();
        link.clear();
        out_link.clear();
        out.clear();
        leaf.clear();
        counter.clear();
        dictionary.clear();
        N = P = 0;
        node();

    }
    bool isEmpty(){
        return P == 0;
    }
    int node()
    {
        next.emplace_back(26, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        counter.emplace_back(0);
        leaf.emplace_back(0);
        return N++;
    }
    int add_pattern(const string T)
    {
        int u = 0;
        for (auto c : T)
        {
            if (!next[u][c - 'a'])
                next[u][c - 'a'] = node();
            u = next[u][c - 'a'];
        }
        out[u].push_back(P);
        leaf[u]++;
        dictionary.push_back(T);
        return P++;
    }
    void compute()
    {
        queue<int> q;
        for (q.push(0); !q.empty(); )
        {
            int u = q.front();
            q.pop();
            // automaton:
            for (int c = 0; c < 26; ++c)
            {
                int v = next[u][c];
                if (!v)
                    next[u][c] = next[link[u]][c];
                else
                {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    counter[v] = counter[out_link[v]] + leaf[v];
                    q.push(v);
                }
            }
        }
    }
    int advance(int u, char c)
    {

        while (u && !next[u][c - 'a'])
            u = link[u];
        u = next[u][c - 'a'];
        return u;
    }
    LL count(const string S)
    {
        LL ans = 0;
        int u = 0;
        for (int i = 0; i < S.size(); ++i)
        {
            char c = S[i];
            u = advance(u, c);
            ans += counter[u];
        }
        return ans;
    }
};

struct DynamicAho{
    AC ar[LOG];

    DynamicAho(){
        for(int i = 0;i < LOG;i++)ar[i].clear();
    }
    void insert(const string S){
        int k = 0;
        for( ;k < LOG and !ar[k].isEmpty();k++){}

        ar[k].add_pattern(S);
        for(int i = 0;i < k;i++){
            for(auto s : ar[i].dictionary){
                ar[k].add_pattern(s);
            }
            ar[i].clear();
        }
        ar[k].compute();
    }
    LL count(const string str){
        LL res = 0;
        for (int i = 0; i < LOG; i++) res += ar[i].count(str);
        return res;
    }
};

int main()
{
    FastRead
    DynamicAho aho[2];
    int q;
    cin >> q;
    while(q--){
        int tp;string s;
        cin >> tp >> s;
        if(tp == 1)aho[0].insert(s);
        else if(tp == 2)aho[1].insert(s);
        else {
            cout << aho[0].count(s) - aho[1].count(s) << endl;
        }
    }

}
