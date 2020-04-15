#include<bits/stdc++.h>

using namespace std;

#define fRead(x)        freopen(x,"r",stdin)
#define fWrite(x)       freopen (x,"w",stdout)

#define LL              long long
#define ULL             unsigned long long
#define ff              first
#define ss              second
#define pb              push_back
#define INF             1e9
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

const int bignumlen=2200;
const int Blen=8;
const LL base=100000000;
struct bignum{
	int len;
	LL data[bignumlen];
	LL &operator [](int x){ return(data[x]);}
	const LL &operator [](int x)const { return(data[x]);}
	bignum (){
		memset(data,0,sizeof(data));
		len=0;
	}
	void clear(){
		for(int i=len;i>=1;--i)data[i]=0;
		len=0;
	}
	int check (const bignum &a,const bignum &b){
		if(a.len>b.len)return(0);
		if(b.len>a.len)return(1);
		for(int i=a.len;i>=1;--i){
			if(a.data[i]<b.data[i])return(1);
			if(b.data[i]<a.data[i])return(0);
		}
		return 2;
	}
	bool operator < (const bignum &b){ return(check(*this,b)==1);}
	bool operator > (const bignum &b){ return(check(*this,b)==0);}
	bool operator <=(const bignum &b){ return(check(*this,b)>=1);}
	bool operator >=(const bignum &b){ return(check(*this,b)%2==0);}
	bool operator !=(const bignum &b){ return(check(*this,b)!=2);}
	bool operator ==(const bignum &b){ return(check(*this,b)==2);}

	bignum operator=(const bignum &x){
		for(int i=x.len+1;i<=len;++i)data[i]=0;
		for(int i=1;i<=x.len;++i)data[i]=x.data[i];
		len=x.len;
		return *this;
	}
	bignum operator=(LL x){
		for(int i=len;i>=0;--i)data[i]=0;
		len=0;
		while(x){
			data[++len]=x%base;
			x/=base;
		}
		return *this;
	}
	bignum(LL x){
		memset(data,0,sizeof(data));
		len=0;
		(*this)=x;
	}
	bignum operator *(const bignum &b){
		int i,j;
		bignum tmp;
		for(i=1;i<=len;++i)if(data[i]!=0)
			for(j=1;j<=b.len;++j)if(b.data[j]!=0){
				tmp.data[i+j-1]+=data[i]*b.data[j];
				tmp.data[i+j]+=tmp.data[i+j-1]/base;
				tmp.data[i+j-1]%=base;
			}
		tmp.len=len+b.len-1;
		while(tmp.data[tmp.len+1])tmp.len++;
		return tmp;
	}
	bignum operator *(LL x){
		int i;
		bignum tmp;
		for(i=1;i<=len;++i)tmp[i]=data[i]*x;
		tmp.len=len;
		for(i=1;i<=len;++i){
			tmp[i+1]+=tmp[i]/base,tmp[i]%=base;
			if(tmp[i+1]&&i+1>tmp.len)tmp.len++;
		}
		return tmp;
	}
	bignum operator /(LL x){
		int i;
		bignum tmp;
		LL y=0;
		for(i=len;i>=1;--i){
			y=y*base+data[i];
			tmp[i]=y/x;
			y%=x;
		}
		tmp.len=len;
		while(tmp[tmp.len]==0&&tmp.len>1)tmp.len--;
		return tmp;
	}
	bignum operator /(const bignum &b){
		if(b.len<=1 && b[1]==0){
			printf("error! 被0除!");
			for(;;);
		}
		int i,l1=(len-1)*Blen,l2=(b.len-1)*Blen;
		LL x=data[len],y=b[b.len];
		while(x)x/=10,l1++;
		while(y)y/=10,l2++;
		bignum tmp,chu,B;
		chu=*this; B=b;

		for(i=1;i*Blen<=l1-l2;++i)B*=base;
		for(i=1;i<=(l1-l2)%Blen;++i)B*=10;
		for(i=l1-l2;i>=0;--i){
			x=0;
			while(chu>=B)chu-=B,x++;
			tmp[i/Blen+1]=tmp[i/Blen+1]*10+x;
			B/=10;
		}
		tmp.len=(l1-l2)/Blen+1;
		while(tmp.len>=1 && !tmp[tmp.len])tmp.len--;
		return tmp;
	}
	bignum operator +(const bignum &b){
		bignum tmp;
		int i,l=max(len,b.len);
		for(i=1;i<=l;++i)tmp[i]=data[i]+b[i];
		for(i=1;i<=l;++i)tmp[i+1]+=tmp[i]/base,tmp[i]%=base;
		tmp.len=l;
		if(tmp[tmp.len+1])tmp.len++;
		return tmp;
	}
	bignum operator +(LL x){
		bignum tmp; tmp=*this;
		tmp[1]+=x;
		for(int i=1;i<=len&&tmp[i]>=base;++i)tmp[i+1]+=tmp[i]/base,tmp[i]%=base;
		while(tmp[tmp.len+1])tmp.len++;
		return tmp;
	}
	bignum operator -(const bignum &b){
		int i;
		bignum tmp;
		for(i=1;i<=len;++i)tmp.data[i]=data[i]-b.data[i];
		for(i=1;i<=len;++i){
			if(tmp[i]<0)tmp.data[i]+=base,tmp.data[i+1]--;
		}
		tmp.len=len;
		while(tmp[tmp.len]==0&&tmp.len>1)tmp.len--;
		return tmp;
	}
	bignum operator -(LL x){
		bignum tmp; tmp=*this;
		tmp[1]-=x;
		for(int i=1;i<=len&&tmp[i]<0;++i){
			tmp[i+1]+=(tmp[i]+1)/base-1;
			tmp[i]=(tmp[i]+1)%base+base-1;
		}
		while(!tmp[tmp.len]&&tmp.len>1)tmp.len--;
		return tmp;
	}
	LL operator %(LL x){
		int i;
		LL y=0;
		for(i=len;i>=1;--i)y=(y*base+data[i])%x;
		return y;
	}
	bignum operator %(const bignum &b){
		if(b.len<=1 && b[1]==0){
			printf("error! 被0 mod!");
			for(;;);
		}
		int i,l1=(len-1)*Blen,l2=(b.len-1)*Blen;
		LL x=data[len],y=b[b.len];
		while(x)x/=10,l1++;
		while(y)y/=10,l2++;
		bignum chu,B;
		chu=*this; B=b;

		for(i=1;i*Blen<=l1-l2;++i)B*=base;
		for(i=1;i<=(l1-l2)%Blen;++i)B*=10;
		for(i=l1-l2;i>=0;--i){
			while(chu>=B)chu-=B;
			B/=10;
		}
		return chu;
	}

	bignum operator +=(const bignum &b){return *this=(*this+b);}
	bignum operator *=(const bignum &b){return *this=(*this*b);}
	bignum operator -=(const bignum &b){return *this=(*this -b);}
	bignum operator /=(const bignum &b){return *this=(*this/b);}
	bignum operator %=(const bignum &b){return *this=(*this%b);}
	bignum operator *=(LL x) {return( *this=(*this *x));}
	bignum operator +=(LL x) {return( *this=(*this +x));}
	bignum operator -=(LL x) {return( *this=(*this -x));}
	bignum operator /=(LL x) {return( *this=(*this /x));}
	void read(){
		char c[bignumlen*Blen+10];
		scanf("%s",c+1);
		int l=strlen(c+1);
		(*this).clear();
		LL x;
		for(int i=1;i<=(l-1)/Blen+1;++i){
			x=0;
			for(int j=l-Blen*i+1;j<=l-Blen*i+Blen;++j)if(j>=1)x=x*10+c[j]-48;
			data[++len]=x;
		}
	}
	void write(){
		printf("%lld",data[len]);
		for(int i=len-1;i>=1;--i)printf("%0*lld",Blen,data[i]);
	}
}p,q,pp,qq;
bignum gcd(const bignum &A,const bignum &B){
	bignum a=A,b=B,res=1;
	while(!(a[1]&1)  && !(b[1]&1))a/=2,b/=2,res*=2;
	for(;;){
		if(a.len==1 && a[1]==0)return b*res;
		if(b.len==1 && b[1]==0)return a*res;
		while(!(a[1]&1))a/=2;
		while(!(b[1]&1))b/=2;
		if(a>b)a-=b;
		else b-=a;
	}
}

int main()
{
    fRead("china.in");
    fWrite("china.out");
    bignum N;
    N.read();

    if(N % 2 == 1)(N/2).write();
    else{
        bignum X = N/2 - 1;
        if(gcd(N,X) == 1)X.write();
        else (X - 1).write();
    }
}
