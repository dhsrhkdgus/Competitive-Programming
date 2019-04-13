struct BipartiteMatching {
	int n;
	vector<vector<int>> graph;
	vector<int> check;
	vector<int> match, matched;
	int step;

	BipartiteMatching(int n) : n(n) {
		graph.resize(n);
		check.resize(n);
		match.resize(n, -1);
		matched.resize(n, -1);
	}

	void addEdge(int u, int v) {
		graph[u].push_back(v);
	}

	bool dfs(int x) {
		if(x == -1) return true;
		for(int next : graph[x]) {
			if(check[next] == step) continue;
			check[next] = step;
			if(dfs(matched[next])) {
				matched[next] = x;
				match[x] = next;
				return true;
			}
		}
		return false;
	}

	int flow() {
		int ans = 0;
		for(int i = 0; i < n; i++) {
			step = i+1;
			if(dfs(i)) ans++;
		}
		return ans;
	}
};
