int par[MAXN][LOGN];	// par[v][i]: (2^i)th parent of v
int level[MAXN];	// level[v]: level of v (distance from root)

void dfsLevel(int node, int pnode) {
	for(auto cnode : adj[node]) {
		if(cnode != pnode) {
			par[cnode][0] = node;
			level[cnode] = level[node] + 1;
			dfsLevel(cnode, node);
		}
	}
}

void findPar() {
	for(int i = 1; i < LOGN; i++) {
		for(int node = 0; node < n; node++) {
			par[node][i] = par[par[node][i-1]][i-1];
		}
	}
}

int lca(int u, int v) {
	if(level[u] > level[v]) swap(u, v);
	int d = level[v] - level[u];

	// make u, v same level
	for(int i = 0; i < LOGN; i++) {
		if(d & (1 << i)) {
			v = par[v][i];
		}
	}

	if(u == v) return u;

	// find LCA
	for(int i = LOGN - 1; i >= 0; i--) {
		if(par[u][i] != par[v][i]) {
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}
