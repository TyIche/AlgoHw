#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 1010;

#define lson o<<1
#define rson o<<1|1
#define MID int m = (l + r) >> 1


//列线段树，用来维护列的节点
struct Nodey {
	int Max, Min;

	Nodey operator+(const struct Nodey &t) {
		Nodey rst;
		rst.Max = max(Max, t.Max);
		rst.Min = min(Min, t.Min);
		return rst;
	}
};

int locy[MAX], locx[MAX];


//行线段树，用来维护行的节点
struct Nodex {
	Nodey sty[MAX << 2];

	void build(int o, int l, int r) {
		sty[o].Max = -INF;
		sty[o].Min = INF;
		if (l == r) {
			locy[l] = o;
			return;
		}
		MID;
		build(lson, l, m);
		build(rson, m + 1, r);
	}

	Nodey query(int o, int l, int r, int ql, int qr) {
		if (qr < l || r < ql) return (Nodey) {-INF, INF};
		if (ql <= l && r <= qr) return sty[o];
		MID;
		return query(lson, l, m, ql, qr) + query(rson, m + 1, r, ql, qr);
	}
} stx[MAX << 2];

int n,m;

void build(int o, int l, int r) {
	stx[o].build(1, 1, m);
	if (l == r) {
		locx[l] = o;
		return;
	}
	MID;
	build(lson, l, m);
	build(rson, m + 1, r);
}


//进行单点更新，这里首先更新了叶子节点，然后向上合并父亲节点；
void Modify(int x, int y, int val) {
	int tx = locx[x];
	int ty = locx[y];
	stx[tx].sty[ty].Min = stx[tx].sty[ty].Max = val;
	for (int i = tx; i; i >>= 1) {
		for (int j = ty; j; j >>= 1) {
			if (i == tx && j == ty) continue;
			if (j == ty) {
				//如果当前更新的列就是需要更新的叶子节点，那么由当前行的两个儿子节点来更新信息
				stx[i].sty[j] = stx[i << 1].sty[j] + stx[i << 1 | 1].sty[j];
			} else {
				//否则由当前列的如果儿子节点来更新
				stx[i].sty[j] = stx[i].sty[j << 1] +  stx[i].sty[j << 1 | 1];
			}
		}
	}
}

Nodey query(int o, int l, int r, int ql, int qr, int y1, int y2) {
	if (qr < l || r < ql) return (Nodey) {-INF, INF};
	if (ql <= l && r <= qr) return stx[o].query(1, 1, n, y1, y2);
	MID;
	return query(lson, l, m, ql, qr, y1, y2) + query(rson, m + 1, r, ql, qr, y1, y2);
}


int main() {
	int T;
	n = 20,m = 8;
	build(1,1,n);
	Modify(11,6,10);
	cout<<query(1,1,n,1,11,1,5).Max<<endl;
}
