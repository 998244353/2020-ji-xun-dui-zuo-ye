#include <cstdio>
#include <cstring>
#include <algorithm>
#include <chrono>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MAXN=2200;
const int P=1E9+7;
const int BASE=rng()%19260817+131;
const int MOD=1004535809;
int n, m;
char a[2][MAXN], b[MAXN];
int pre[2][MAXN], suf[2][MAXN], hsh[MAXN];
int powb[MAXN], f[MAXN][2][MAXN];
int get_pre(int k, int l, int r)
{
	return (pre[k][r]-1ll*pre[k][l-1]*powb[r-l+1]%MOD+MOD)%MOD;
}
int get_suf(int k, int l, int r)
{
	return (suf[k][l]-1ll*suf[k][r+1]*powb[r-l+1]%MOD+MOD)%MOD;
}
int solve()
{
	memset(f, 0, sizeof f);
	for (int i=0; i<=n; i++)
		f[0][0][i]=f[0][1][i]=1;
	for (int i=1; i<=n; i++)
		for (int j=i+1; j<=n; j++)
		{
			int l=j-i+1; if (2*l>m) continue;
			if ((1ll*get_suf(1, i, j)*powb[l]+get_pre(0, i, j))%MOD==hsh[2*l])
				f[2*l][0][j]++;
			if ((1ll*get_suf(0, i, j)*powb[l]+get_pre(1, i, j))%MOD==hsh[2*l])
				f[2*l][1][j]++;
		}
	for (int k=1; k<=m; k++)
		for (int i=0; i<=1; i++)
			for (int j=1; j<=n; j++)
				if (a[i][j]==b[k])
				{
					f[k][i][j]=(f[k][i][j]+f[k-1][i][j-1])%P;
					if (k>1&&a[i^1][j]==b[k-1])
						f[k][i][j]=(f[k][i][j]+f[k-2][i^1][j-1])%P;
				}
	int ret=0;
	for (int i=0; i<=n; i++)
		ret=((unsigned)ret+f[m][0][i]+f[m][1][i])%P;
	for (int i=1; i<=n; i++)
		for (int j=i+1; j<=n; j++)
		{
			int l=j-i+1; if (2*l>m) continue;
			int t=(hsh[m]-1ll*hsh[m-2*l]*powb[2*l]%MOD+MOD)%MOD;
			if ((1ll*get_pre(0, i, j)*powb[l]+get_suf(1, i, j))%MOD==t)
				ret=(ret+f[m-2*l][0][i-1])%P;
			if ((1ll*get_pre(1, i, j)*powb[l]+get_suf(0, i, j))%MOD==t)
				ret=(ret+f[m-2*l][1][i-1])%P;
		}
	return ret;
}
int main()
{
//	freopen("CF613E.in", "r", stdin);
//	freopen("CF613E.out", "w", stdout);
	scanf("%s%s%s", a[0]+1, a[1]+1, b+1);
	n=strlen(a[0]+1), m=strlen(b+1);
	powb[0]=1;
	for (int i=1; i<=max(n, m); i++)
		powb[i]=1ll*powb[i-1]*BASE%MOD;
	for (int i=0; i<=1; i++)
	{
		for (int j=1; j<=n; j++)
			pre[i][j]=(1ll*pre[i][j-1]*BASE+a[i][j])%MOD;
		for (int j=n; j>=1; j--)
			suf[i][j]=(1ll*suf[i][j+1]*BASE+a[i][j])%MOD;
	}
	for (int i=1; i<=m; i++)
		hsh[i]=(1ll*hsh[i-1]*BASE+b[i])%MOD;
	int ans=solve();
	if (m!=1)
	{
		reverse(b+1, b+m+1);
		for (int i=1; i<=m; i++)
			hsh[i]=(1ll*hsh[i-1]*BASE+b[i])%MOD;
		ans=(ans+solve())%P;
	}
	for (int i=1; i<=n; i++)
		for (int j=i; j<=n; j++)
		{
			int l=j-i+1;
			if (2*l!=m) continue;
			ans-=(1ll*get_suf(1, i, j)*powb[l]+get_pre(0, i, j))%MOD==hsh[m];
			ans-=(1ll*get_suf(0, i, j)*powb[l]+get_pre(1, i, j))%MOD==hsh[m];
			if (l==1) continue;
			ans-=(1ll*get_pre(1, i, j)*powb[l]+get_suf(0, i, j))%MOD==hsh[m];
			ans-=(1ll*get_pre(0, i, j)*powb[l]+get_suf(1, i, j))%MOD==hsh[m];
		}
	ans=(ans+P)%P;
	printf("%d\n", ans);
	return 0;
}
