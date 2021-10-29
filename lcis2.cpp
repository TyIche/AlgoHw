#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAX = 1010;

#define lson o<<1
#define rson o<<1|1
#define MID int m = (l + r) >> 1

// struct lll{
// 	int x,pos1,pos2;
// }bu[MN*2],dp[MN][MN];
vector<int>v;
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

int n;

void build(int o, int l, int r) {
    stx[o].build(1, 1, n);
    if (l == r) {
        locx[l] = o;
        return;
    }
    MID;
    build(lson, l, m);
    build(rson, m + 1, r);
}
void Modify(int x, int y, int val) {
    int tx = locx[x];
    int ty = locx[y];
    stx[tx].sty[ty].Min = stx[tx].sty[ty].Max = val;
    for (int i = tx; i; i >>= 1) {
        for (int j = ty; j; j >>= 1) {
            if (i == tx && j == ty) continue;
            if (j == ty) {
                stx[i].sty[j] = stx[i << 1].sty[j] + stx[i << 1 | 1].sty[j];
            } else {
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

    cin>>n>>m;
	so(i,1,n,1) cin>>a[i],A[i] = a[i];
//	so(i,1,n,1) cout<<a[i]<<" ";cout<<endl;
	so(i,1,m,1) cin>>b[i],A[n+i] = b[i];
//	so(i,1,m,1) cout<<b[i]<<" ";cout<<endl;
	sort(A+1,A+1+n+m);
	so(i,1,n,1) a[i] = lower_bound(A+1,A+1+n+m,a[i])-A;
	so(i,1,m,1) b[i] = lower_bound(A+1,A+1+m+n,b[i])-A;

    modify(1,1,0);
    so(i,1,n,1) {
		
		v.clear();
		so(j,1,m,1)
		{
			if(a[i] == b[j]) 
			{
				dp[i][j] =  get(a[i]) + 1;
				v.push_back(make_pair(j,dp[i][j]));
				//add(a[i],tmp);
			}
			else dp[i][j] = get(max(n,m));
		}
		for(auto i : v){
			add(j,i.second);
		}
	}
	// so(i,1,n,1)
	// {
	// 	so(j,1,m,1) cout<<dp[i][j].x<<" ";cout<<endl;
	// }
	// cout<<"1ok"<<endl;
	// int x = n,y = m;
	// if(dp[n][m].x >= dp[dp[n][m].pos1][dp[n][m].pos2].x)
	// 	ans.push_back(a[n]);
	// while(x!=-1&&y!=-1)
	// {
	// 	cout<<x<<" "<<y<<endl;
	// 	ans.push_back(a[dp[x][y].pos1]);
	// 	lll tmp = dp[x][y];
	// 	x = tmp.pos1;y = tmp.pos2;
	// }
	// cout<<"2ok"<<endl;
	// reverse(ans.begin(),ans.end());
	// for(auto i : ans)
	// {
	// 	cout<<ans[i]<<" ";
	// }
    cout<<dp[n][m];
	cout<<endl;

}