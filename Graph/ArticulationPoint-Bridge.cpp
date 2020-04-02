#define MAX 10005
vector<int> G[MAX];
vector<pair<int, int> > bridges;
int low[MAX], vis[MAX], artPoint[MAX], visTime, noc;

void articulationPointAndBridge(int u, int par=-1){
	low[u]=vis[u]=++visTime;
	for(int j=0; j<(int)G[u].size(); j++){
		int v=G[u][j];
		if(v==par) continue; /// back-edge to direct parent
		if(!vis[v]){ /// A tree edge
			articulationPointAndBridge(v, u);
			if(low[v]>=vis[u]) artPoint[u]=true; /// Can't reach back to it's anchestor
			if(low[v]>vis[u]) bridges.push_back({u, v}); /// Can't reach back to u or it's anchestor
			low[u]=min(low[u], low[v]);
			if(par==-1) noc++;
		}
		else low[u]=min(low[u], vis[v]); /// A back-edge
	}
}

void processAPB(int n){ /// 0 indexed
	for(int i=0; i<n; i++) low[i]=vis[i]=artPoint[i]=0; visTime=0;
	bridges.clear();
	for(int i=0; i<n; i++){
		if(!vis[i]){
			noc=0; articulationPointAndBridge(i);
			artPoint[i]=(noc>1); /// special case, noc(number of components of root node)
		}
	}
}
