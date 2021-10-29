#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r); i++)
#define per(i,r,l) for(int i=(r);i>=(l); i--)
#define so(i,j,k,l) for(int i = j;i <= k;i += l)
#define MN 5050
#define INF 2147483647
using namespace std;
vector<int>ans;
int n,m,a[MN],b[MN],A[MN],B[MN];

struct lll{
	int x,pos1,pos2;
}bu[MN*2],dp[MN][MN];
vector<pair<int,lll> >v;
int lb(int x)
{
	return x& -x;
}
void add(int pos,lll a)
{
	for(;pos<=max(n,m);pos += lb(pos))
		if(a.x > bu[pos].x) bu[pos] = a;
}
lll get(int pos)
{
	lll ret = {-INF,-1,-1};
	for(;pos>0;pos -= lb(pos))
		if(ret.x < bu[pos].x) ret = bu[pos];
	return ret;
}
int main(){
	
	cin>>n>>m;
	so(i,0,2*max(n,m),1) bu[i].x = -INF;
	so(i,1,n,1) cin>>a[i],A[i] = a[i];
//	so(i,1,n,1) cout<<a[i]<<" ";cout<<endl;
	so(i,1,m,1) cin>>b[i],A[n+i] = b[i];
//	so(i,1,m,1) cout<<b[i]<<" ";cout<<endl;
	sort(A+1,A+1+n+m);
	so(i,1,n,1) a[i] = lower_bound(A+1,A+1+n+m,a[i])-A;
	so(i,1,m,1) b[i] = lower_bound(A+1,A+1+m+n,b[i])-A;
	

	so(i,1,n,1) cout<<a[i]<<" ";cout<<endl;
	so(i,1,m,1) cout<<b[i]<<" ";cout<<endl;
	add(1,{0,-1,-1});
	so(i,1,n,1) {
		
		v.clear();
		so(j,1,m,1)
		{
			if(a[i] == b[j]) 
			{
				dp[i][j] =  get(a[i]);
				dp[i][j].x +=1;
				lll tmp = dp[i][j];tmp.pos1 = i;tmp.pos2 = j;
				v.push_back(make_pair(a[i],tmp));
				//add(a[i],tmp);
			}
			else dp[i][j] = get(max(n,m));
		}
		for(auto i : v){
			add(i.first,i.second);
		}
	}
	so(i,1,n,1)
	{
		so(j,1,m,1) cout<<dp[i][j].x<<" ";cout<<endl;
	}
	cout<<"1ok"<<endl;
	int x = n,y = m;
	if(dp[n][m].x >= dp[dp[n][m].pos1][dp[n][m].pos2].x)
		ans.push_back(a[n]);
	while(x!=-1&&y!=-1)
	{
		cout<<x<<" "<<y<<endl;
		ans.push_back(a[dp[x][y].pos1]);
		lll tmp = dp[x][y];
		x = tmp.pos1;y = tmp.pos2;
	}
	cout<<"2ok"<<endl;
	reverse(ans.begin(),ans.end());
	for(auto i : ans)
	{
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	return 0;
}
