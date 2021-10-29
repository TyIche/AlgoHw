#include<bits/stdc++.h>
using namespace std;
#define db double
#define so(i,j,k,l) for(int i = j;i <= k;i += l)
db RNG()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> rng(-1e7,1e7);
    return rng(gen);
}
int main()
{
    freopen("in.txt","w",stdout);
    int now = 10;
    so(i,1,7,1)
    {
        //cout<<now<<endl;
        printf("%d\n",now);
        so(j,1,now,1) printf("%lf ",RNG());
        puts("");
        // now*=10;
    }
    //cout<<"quq"<<endl;
}