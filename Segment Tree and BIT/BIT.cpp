namespace BIT{
    const int N = 400005;
    int bit[N];
    void update(int idx,int val){
        while(idx < N){
            bit[idx] += val;
            idx += (idx&-idx);
        }
    }
    int query(int idx){
        int ret = 0;
        while(idx > 0){
            ret += bit[idx];
            idx -= (idx&-idx);
        }
        return ret;
    }
}

namespace BIT2D{
    const int N = 400005;
    const int M = 61;
    int bit[M][N];

    void update(int id,int idx,int val){
        while(idx < N){
            bit[id][idx] += val;
            idx += (idx&-idx);
        }
    }
    int query(int id,int idx){
        int ret = 0;
        while(idx > 0){
            ret += bit[id][idx];
            idx -= (idx&-idx);
        }
        return ret;
    }
}
