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

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("input.txt", "r", stdin)

char str[MAX];
int s0[(MAX / 3) + 10], sa0[(MAX / 3) + 10];
int n, ar[MAX], sa[MAX], lcp[MAX], bucket[MAX], mem[MAX << 2];

void radixsort(int* source, int* dest, int* val, int n, int lim){ /// hash = 349247
    int i, s = 0, x;
    memset(bucket, 0, lim << 2);
    for (i = 0; i < n; i++) bucket[val[source[i]]]++;

    for (i = 0; i < lim; i++){
        x = bucket[i];
        bucket[i] = s, s += x;
    }
    for (i = 0; i < n; i++) dest[bucket[val[source[i]]]++] = source[i];
}

void DC3(int* ar, int* sa, int n, int lim, int ptr){ /// hash = 758459
    int *s12, *sa12;
    int allc = (n / 3) << 1, n0 = (n + 2) / 3;
    int i, j, k, l, c, d, p, t, m, r, counter;
    s12 = &mem[ptr], ptr += (allc + 5), sa12 = &mem[ptr], ptr += (allc + 5);

    c = 0, m = 0, r = n + ((n % 3) == 1);
    for (i = 0; i < r; i++, m++){
        if (m == 3) m = 0;
        if (m) s12[c++] = i;
    }
    s12[c] = sa12[c] = s12[c + 1] = sa12[c + 1] = s12[c + 2] = sa12[c + 2] = 0;
    radixsort(s12, sa12, ar + 2, c, lim + 1);
    radixsort(sa12, s12, ar + 1, c, lim + 1);
    radixsort(s12, sa12, ar, c, lim + 1);

    counter = 0, j = -1;
    for (i = 0; i < c; i++){
        if ((ar[sa12[i]] != j) || (ar[sa12[i] + 1] != k) || (ar[sa12[i] + 2] != l)){
            counter++;
            j = ar[sa12[i]], k = ar[sa12[i] + 1], l = ar[sa12[i] + 2];
        }
        if((sa12[i] % 3) == 1) s12[sa12[i] / 3] = counter;
        else s12[(sa12[i] / 3) + n0] = counter;
    }

    if (counter == c){
        for(i = 0; i < c; i++) sa12[s12[i] - 1] = i;
    }
    else{
        DC3(s12, sa12, c, counter, ptr);
        for (i = 0; i < c; i++) s12[sa12[i]] = i + 1;
    }

    for (i = 0, d = 0; i < c; i++){
        if (sa12[i] < n0) s0[d++] = (sa12[i] * 3);
    }
    radixsort(s0, sa0, ar, d, lim + 1);
    for (k = 0, l = ((n % 3) == 1), r = 0; r < n; r++){
        j = sa0[k];
        i = ((sa12[l] < n0) ? (sa12[l] * 3) + 1 : ((sa12[l] - n0) * 3) + 2);
        if (l == c) sa[r] = sa0[k++];
        else if (k == d) sa[r] = i, l++;
        else{
            if (sa12[l] < n0){
                if ((ar[i] < ar[j]) || (ar[i] == ar[j] && s12[sa12[l] + n0] <= s12[j / 3])) sa[r] = i, l++;
                else sa[r] = j, k++;
            }
            else{
                if ((ar[i] < ar[j]) || (ar[i] == ar[j] && ar[i + 1] < ar[j + 1]) || (ar[i] == ar[j] && ar[i + 1] == ar[j + 1] && s12[sa12[l] - n0 + 1] <= s12[(j / 3) + n0]) ) sa[r] = i, l++;
                else sa[r] = j, k++;
            }
        }
    }
}

void LcpArray(){ /// hash = 935019
    int i, j, k;
    for (i = 0; i < n; i++) ar[sa[i]] = i;

    for (k = 0, i = 0; i < n; i++, k?k--:0){
        if (ar[i] == (n - 1)) k = 0;
        else{
            j = sa[ar[i] + 1];
            while(((i + k) < n) && ((j + k) < n) && (str[i + k] == str[j + k])) k++;
        }
        lcp[ar[i]] = k;
    }
}

void Generate(){
    int i, j, lim = 0;
    for (i = 0; i < n; i++){
        ar[i] = str[i];
        if (ar[i] > lim) lim = ar[i];
    }

    ar[n] = ar[n + 1] = ar[n + 2] = 0;
    DC3(ar, sa, n, lim, 0);
    LcpArray();
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%s",str);
        n = strlen(str);
        Generate();

        int idx ;
        for(idx = 0; idx < n; idx++) printf("(%d, %d) ", ar[idx], sa[idx]); printf("\n");
        for(idx = 0; idx < n; idx++){
            printf("%s\n",str + sa[idx]);
        }

        for(idx = 0; idx < n - 1; idx++) printf("%d ", lcp[idx]);
    }
}
