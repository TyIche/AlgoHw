#include<bits/stdc++.h>
using namespace std;
#define so(i,j,k,l) for(int i = j;i <= k;i += l)
#define db double
#define LL long long
#define MN 10000050
int n;
db A[MN],a[MN],b[MN],L[MN],R[MN],tmp[MN];
void P()
{
    so(i,1,n,1) cout<<a[i]<<" ";puts("");
}
void move(int l,int r)
{
    if(l > r) return;
    for(int i = r;i >= l;i--)
    swap(b[i+1],b[i]);
}
void Isort()
{
    so(i,1,n,1) a[i] = A[i];
    // so(i,1,n,1) cout<<a[i]<<" ";cout<<endl;
    int tot = 0;
    b[1] = 1e18;
    so(i,1,n,1)
    {
        int f = 0;
        so(j,1,tot,1)
        {
            if(b[j] > a[i]) 
            {
                move(j,tot);
                b[j] = a[i];tot++;
                b[tot+1] = 1e18;
                f = 1;
                break;

            }
        }
        if(!f) {swap(b[tot+1],b[tot+2]);b[++tot] = a[i];}

        // so(i,1,tot+1,1) cout<<b[i]<<" ";cout<<endl;
    }
    so(i,1,n,1) a[i] = b[i];
}
void Msort(int l,int r)
{
    if(l == r) return;
    int mid = (l + r)>>1;
    Msort(l,mid);Msort(mid+1,r);
    int Ll = mid - l + 1,Lr = r - mid;
    so(i,l,mid,1) L[i - l + 1] = a[i];
    so(i,mid+1,r,1) R[i - mid] = a[i];
    int p1 = 0,p2 = 0;
    so(i,l,r,1)
    {
        if(p1 >= Ll)
        {
            tmp[i] = R[++p2];
        }
        else if(p2 >= Lr)
        {
            tmp[i] = L[++p1];
        }
        else
        {
            if(R[p2+1] < L[p1+1])tmp[i] = R[++p2];
            else tmp[i] = L[++p1];
        }
    }
    so(i,l,r,1) a[i] = tmp[i];
}
int RNG(int l,int r)
{
    random_device d;
    mt19937 gen(d());
    uniform_int_distribution<>rng(l,r);
    return rng(gen);
}
void Qsort(int l,int r)
{
    if(l == r)
    {
        return ;
    }
    int mid = RNG(l,r-1);
    int L = l,R = r;
    so(i,l,r,1) 
    {
        if(i == mid) continue;
        if(a[i] < a[mid]) tmp[L++] = a[i];else tmp[R--] = a[i];
    }
    tmp[L] = a[mid];
    so(i,l,r,1) a[i] = tmp[i];
    Qsort(l,mid);Qsort(mid+1,r);
}
int main()
{
    freopen("in.txt","r",stdin);
    int Aa = 7,B = 1000;
    so(i,1,Aa,1)
    {
               
        LL timeI= 0 ,timeM = 0,timeQ = 0;
        so(j,1,B,1)
        {cout<<i<<" "<<j<<endl;
            scanf("%d",&n);
            so(k,1,n,1)
            {
                scanf("%lf",&A[k]);
            }
            LL iii = clock();
            // Isort();
            timeI+= clock() - iii;
            so(i,1,n,1) a[i] = A[i];
            // so(i,1,n,1) cout<<a[i]<<" ";cout<<endl;
            // P();
            Msort(1,n);
            timeM += clock() - iii;
            // P();
            so(i,1,n,1) a[i] = A[i];
            Qsort(1,n);
            timeQ += clock() - iii;
            // P();
        }
    }
}