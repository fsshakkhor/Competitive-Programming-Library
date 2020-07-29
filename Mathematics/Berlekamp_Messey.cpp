/// Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vll;

#define FORR(i, x, y)        for(int i=int(x); i<int(y); i++)
#define all(c)              c.begin(), c.end()

template <class T> inline T bigMod(T p,T e,T M){ T ret = 1; for(; e > 0; e >>= 1){ if(e & 1) ret = (ret * p) % M; p = (p * p) % M; } return (T) ret;}
template <class T> inline T modInverse(T a,T M){return bigMod(a,M-2,M);}

#define mType  int
#define matrix vector<vector<mType>>

int mod;
inline matrix Identity_Matrix(const int row, const int col){
    matrix I(row,vector<mType>(col,0));
    for(int i = 0; i < row; i++) I[i][i] = 1;
    return I;
}
inline matrix operator *(const matrix &a, const matrix &b){
    int ra = a.size(), ca = a[0].size();
    int rb = b.size(), cb = b[0].size();
    if(ca != rb) return Identity_Matrix(ra,cb);

    __int128 sum;
    matrix res(ra,vector<mType>(cb));
    for(int i = 0; i < ra; i++){
        for(int j = 0; j < cb; j++){
            sum = 0;
            for(int k = 0; k < ca; k++) sum += 1LL*a[i][k]*b[k][j];
            res[i][j] = sum%mod;
        }
    }
    return res;
}
matrix I;
matrix operator ^(const matrix &base, const long long power){
    if(power == 0) return I;
    if(power == 1) return base;
    matrix full = base^(power>>1); // half
    full = full*full; // full = half*half
    if(power&1) full = full*base; // if(power is odd)
    return full;
}

ll convolution(vll _first, vll _second, ll modulo){
    ll result = 0, len = _first.size();
    FORR(i,0,len) result = (result + _first[i] * _second[i]) % modulo;
    return result;
}
vll berlekamp_massey(vll base_sequence, ll modulo){
    int n = base_sequence.size();

    vll U(n + 1, 0),V(n + 1, 0),W;
    U[0] = V[0] = 1;
    reverse(all(base_sequence));

    vll _first,_second;
    ll l = 0, m = 1, b  = 1, deg = 0;
    FORR(i,0,n){
        ll d = base_sequence[n - 1 - i];

        if(l){
            _first.assign(V.begin()+1,V.begin()+1+l);
            _second.assign(base_sequence.begin()+n-i,base_sequence.begin()+n-i+l);
            d = (d + convolution(_first, _second, modulo)) % modulo;
        }
        if(!d){ m += 1; continue;}
        if(l * 2 <= i) W.assign(V.begin(), V.begin()+l+1);

        ll x = (modInverse(b,modulo) * (modulo - d) % modulo + modulo) % modulo;

        FORR(j,0,deg+1) V[m + j] = (V[m + j] + x * U[j]) % modulo;

        if(l * 2 <= i){
            swap(W,U);
            deg = U.size()-1;
            b = d , m = 1, l = i - l + 1;
        }
        else m += 1;
    }

    vll tmp(max(0LL,l-(ll)V.size()+1), 0);
    V.erase(V.begin()+l+1,V.end());
    V.erase(V.begin());
    V.insert(V.end(), all(tmp));

    return V;
}

int solve_linear_recurrence(vll base_sequence, ll nth_term, ll modulo){
    int n = base_sequence.size();
    if(nth_term < n) return base_sequence[nth_term];

    vll recurrence = berlekamp_massey(base_sequence,modulo);

   // for(auto i : recurrence) cout << i << endl;

    int l = recurrence.size();
    I = Identity_Matrix(l,l);
    matrix M(l, vector<mType>(l, 0));
    mod = modulo;
    FORR(i,0,l){
        M[0][i] = modulo - recurrence[i];
        if(i) M[i][i - 1] = 1;
    }

    ll result = 0;
    M = M ^ (nth_term - n + 1);

    FORR(i,0,l) result += M[0][i] * base_sequence[n - i - 1];

    return result % modulo;
}
