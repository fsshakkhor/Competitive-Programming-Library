const int N = 100000;
bool stat[N+5];
vector<int>primes;
void siv()
{
    int sq = sqrt(N);for(int i =4;i<=N;i+=2)stat[i]=1;
    for(int i=3;i<=sq;i+=2)if(!stat[i])for(int j=i*i;j<=N;j+=2*i)stat[j]=1;
    for(int i = 2;i < N;i++)if(!stat[i])primes.push_back(i);
}
