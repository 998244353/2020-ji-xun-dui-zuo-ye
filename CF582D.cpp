#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=3500;
const int MOD=1E9+7;
char s[MAXN]; int a[MAXN];
int f[2][2][MAXN];
int g[2][2][MAXN];
inline void Add(int& x, long long y)
{
	x=(x+y)%MOD;
}
int main()
{
//	freopen("CF582D.in", "r", stdin);
//	freopen("CF582D.out", "w", stdout);
	int p, m, l, n=0;
	scanf("%d%d%s", &p, &m, s);
	l=strlen(s);
	bool flag;
	do
	{
		flag=0;
		long long r=0;
		for (int i=0; i<l; i++)
		{
			r=10*r+s[i]-'0';
			s[i]=r/p+'0', r%=p;
			if (s[i]!='0') flag=1;
		}
		a[n++]=r;
	} while (flag);
	f[1][0][0]=1;
	for (int i=n-1; i>=0; i--)
	{
		int c0=1ll*p*(p+1)/2%MOD;
		int c1=1ll*a[i]*(a[i]+1)/2%MOD;
		int c2=1ll*p*(p-1)/2%MOD;
		int c3=1ll*a[i]*(a[i]-1)/2%MOD;
		int c4=1ll*a[i]*(p+p-a[i]-1)/2%MOD;
		int c5=1ll*a[i]*(p+p-a[i]+1)/2%MOD;
		memset(g, 0, sizeof g);
		for (int j=0; j<n-i; j++)
		{
			int f0=f[0][0][j], f1=f[0][1][j];
			int f2=f[1][0][j], f3=f[1][1][j];
			Add(g[0][0][j], 1ll*f0*c0+1ll*f2*c1);
			Add(g[0][1][j], 1ll*f0*c2+1ll*f2*c3);
			Add(g[1][0][j], 1ll*f2*(a[i]+1));
			Add(g[1][1][j], 1ll*f2*a[i]);
			Add(g[0][0][j+1], 1ll*f1*c2+1ll*f3*c4);
			Add(g[0][1][j+1], 1ll*f1*c0+1ll*f3*c5);
			Add(g[1][0][j+1], 1ll*f3*(p-a[i]-1));
			Add(g[1][1][j+1], 1ll*f3*(p-a[i]));
		}
		swap(f, g);
	}
	int ans=0;
	for (int i=m; i<=n; i++)
		Add(ans, f[0][0][i]+f[1][0][i]);
	printf("%d\n", ans);
	return 0;
}
