#include <bits/stdc++.h>

using namespace std;
#define so(i,j,k,l) for(int i = j;i <= k;i += l)
const int INF = 0x3f3f3f3f;
const int MAX = 1010;
#define MN 2050
#define lson o<<1
#define rson o<<1|1
#define MID int mid = (l + r) >> 1
using namespace std;
struct lll{
	int x,pos1,pos2;
}dp[MN][MN];
vector<int> ans;
bool operator < (lll a,lll b)
{
    return a.x < b.x;
}
struct ll{
    int x,y;lll w;
};
int n,m,a[MN],b[MN],A[MN];
vector<ll >v;
struct Nodey {
    lll Max, Min;

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
        sty[o].Max.x = -INF;
        sty[o].Max.pos1 = sty[o].Max.pos2 = -1;
        sty[o].Min.x = INF;
        if (l == r) {
            locy[l] = o;
            return;
        }
        MID;
        build(lson, l, mid);
        build(rson, mid + 1, r);
    }

    Nodey query(int o, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return (Nodey) {-INF, INF};
        if (ql <= l && r <= qr) return sty[o];
        MID;
        return query(lson, l, mid, ql, qr) + query(rson, mid + 1, r, ql, qr);
    }
} stx[MAX << 2];

void build(int o, int l, int r) {
    stx[o].build(1, 1, m);
    if (l == r) {
        locx[l] = o;
        return;
    }
    MID;
    build(lson, l, mid);
    build(rson, mid + 1, r);
}
void Modify(int x, int y, lll val) {
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
    return query(lson, l, mid, ql, qr, y1, y2) + query(rson, mid + 1, r, ql, qr, y1, y2);
}


int main() {
    //默认 n >= m
    cin>>n>>m;
	build(1,1,n);
	so(i,1,n,1) cin>>a[i],A[i] = a[i];
//	so(i,1,n,1) cout<<a[i]<<" ";cout<<endl;
	so(i,1,m,1) cin>>b[i],A[n+i] = b[i];
//	so(i,1,m,1) cout<<b[i]<<" ";cout<<endl;
	sort(A+1,A+1+n+m);
	so(i,1,n,1) a[i] = lower_bound(A+1,A+1+n+m,a[i])-A;
	so(i,1,m,1) b[i] = lower_bound(A+1,A+1+m+n,b[i])-A;

    Modify(1,1,{0,-1,-1});
	//cout<<query(1,1,n,1,1,1,1).Max<<endl;
    so(i,1,n,1) {
		
		v.clear();
		so(j,1,m,1)
		{
			if(a[i] == b[j]) 
			{
                //if(j == 6) cout<<a[i]<<" "<<j-1<<endl;
                if(j>1)
				dp[i][j] =  query(1,1,n,1,a[i],1,j-1).Max;
                else dp[i][j] = {0,-1,-1};
                dp[i][j].x ++;
                lll tmp = dp[i][j];tmp.pos1 = i;tmp.pos2 = j;
				v.push_back({a[i],j,tmp});
				//add(a[i],tmp);
			}
			else dp[i][j] = query(1,1,n,1,n,1,m).Max;
		}
		for(auto i : v){
			Modify(i.x,i.y,i.w);
            //cout<<"LOG "<<i.x<<" "<<i.y<<" "<<i.w.x<<endl;
		}
	}
	// so(i,1,n,1)
	// {
	// 	so(j,1,m,1) cout<<dp[i][j].x<<" ";cout<<endl;
	// }
	// cout<<"1ok"<<endl;
	int x = n,y = m;
	if(dp[n][m].x > dp[dp[n][m].pos1][dp[n][m].pos2].x)
		ans.push_back(a[n]);
	while(x!=-1&&y!=-1)
	{
        if(~dp[x][y].pos1)
		ans.push_back(A[a[dp[x][y].pos1]]);
		lll tmp = dp[x][y];
		x = tmp.pos1;y = tmp.pos2;
	}
	// cout<<"2ok"<<endl;
	reverse(ans.begin(),ans.end());
	for(auto i : ans)
	{
		cout<<i<<" ";
	}
    
}
/*
11 8
1 2 7 3 4 5 4 2 5 3 6
1 2 5 3 6 4 1 2
*/
