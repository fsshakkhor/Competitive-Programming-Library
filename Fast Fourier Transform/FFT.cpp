#include<bits/stdc++.h>
#define PI acos(-1.0)
#define LL long long
using namespace std;
typedef complex<double> base;

void fft(vector<base> & a, bool invert) {
	int n = (int)a.size();

	for (int i = 1, j = 0; i<n; ++i) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)j -= bit;
		j += bit;
		if (i < j)swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i<n; i += len) {
			base w(1);
			for (int j = 0; j<len / 2; ++j) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)for (int i = 0; i<n; ++i)a[i] /= n;
}
vector<LL> Mul(vector<LL>& a, vector<LL>& b)
{
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while (n < max(a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);

	fft(fa, false), fft(fb, false);
	for (int i = 0; i<n; ++i)fa[i] *= fb[i];
	fft(fa, true);

	vector<LL> res;
	res.resize(n);
	for (int i = 0; i<n; ++i)res[i] = round(fa[i].real());
	return res;
}
const int N = 500005;
LL cnt[N];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while(cin >> n){
        memset(cnt,0,sizeof cnt);
        for(LL i = 1;i < n;i++){
            LL x = (i * i) % n;
            cnt[x]++;
        }
        vector<LL>v1(n),v2(n);
        for(int i = 0;i < n;i++){
            v1[i] = cnt[i];
            v2[i] = cnt[i];
        }

        vector<LL> v = Mul(v1,v2);
        vector<LL>V(n);
        for(int i = 0;i < v.size();i++){
            V[i % n] += v[i];
        }
        while(V.size() > n)V.pop_back();

        for(int i = 0;i < V.size();i++){
            V[(2 * i) % n] = V[(2 * i) % n] - (cnt[i]);
        }

        for(int i = 0;i < V.size();i++){
            V[i] = V[i]/2;
        }

        for(int i = 0;i < V.size();i++){
            V[(2 * i) % n] = V[(2 * i) % n] + (cnt[i]);
        }
        LL ans = 0;
        for(int i = 0;i < V.size();i++){
            ans += V[i] * cnt[i];
        }
        cout << ans << "\n";


    }
}

