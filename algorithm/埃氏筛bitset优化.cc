//bitset 优化

const int N = 1e8 + 10;
bitset<N> vis;
vector<int> pri;
void Prime(int n) {
	vis.set();
  	vis[0] = vis[1] = 0;
  	for(int i = 2; i * i <= n; i++) if(vis[i]) for(int j = i << 1; j <= n; j += i) vis[j] = 0;
  	for(int i = 2; i <= n; i++) if(vis[i]) pri.emplace_back(i);
}

