const int MAXN = 1e6 + 50;
const int LOGN = 17;

ll sum[4 * MAXN], lazy[4 * MAXN];
int n;

// [x, y)와 [l, r)이 겹치지 않아도 lazy propagation을 해야함에 주의
void update(int x, int y, ll val, int l = 0, int r = n, int id = 1) {
	if(x <= l && r <= y)
		lazy[id] += val;

	if(lazy[id] != 0) {
		sum[id] += lazy[id] * (r - l);
		if(r - l > 1) {
			lazy[L(id)] += lazy[id];
			lazy[R(id)] += lazy[id];
		}
		lazy[id] = 0;
	}
	
	if(y <= l || r <= x) return;
	if(x <= l && r <= y) return;

	int mid = (l + r) >> 1;
	update(x, y, val, l, mid, L(id));
	update(x, y, val, mid, r, R(id));
	sum[id] = sum[L(id)] + sum[R(id)];
}


ll rangeSum(int x, int y, int l = 0, int r = n, int id = 1) {
	if(y <= l || r <= x) return 0;
	if(lazy[id] != 0) {
		sum[id] += lazy[id] * (r - l);
		if(r - l > 1) {
			lazy[L(id)] += lazy[id];
			lazy[R(id)] += lazy[id];
		}
		lazy[id] = 0;
	}

	if(x <= l && r <= y) return sum[id];

	int mid = (l + r) >> 1;
	return rangeSum(x, y, l, mid, L(id)) + rangeSum(x, y, mid, r, R(id));
}
