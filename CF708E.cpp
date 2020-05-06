#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=2000;
const int MAXK=110000;
const int P=1E9+7;
int fac[MAXK], ifac[MAXK];
int d[MAXN], s1[MAXN], s2[MAXN];
int f[MAXN], g[MAXN];
int qpow(int n, int k)
{
	int r=1;
	while (k)
	{
		if (k&1) r=1ll*r*n%P;
		n=1ll*n*n%P; k>>=1;
	}
	return r;
}
inline int C(int n, int k)
{
	return 1ll*fac[n]*ifac[k]%P*ifac[n-k]%P;
}
int main()
{
//	freopen("CF708E.in", "r", stdin);
//	freopen("CF708E.out", "w", stdout);
	int n, m, a, b, p, k;
	scanf("%d%d%d%d%d", &n, &m, &a, &b, &k);
	p=1ll*a*qpow(b, P-2)%P;
	fac[0]=1;
	for (int i=1; i<=k; i++) fac[i]=1ll*fac[i-1]*i%P;
	ifac[k]=qpow(fac[k], P-2);
	for (int i=k; i>=1; i--) ifac[i-1]=1ll*ifac[i]*i%P;
	for (int i=0, q=(1-p+P); i<m&&i<=k; i++)
		d[i]=1ll*C(k, i)*qpow(p, i)%P*qpow(q, k-i)%P;
	for (int i=1; i<=m; i++) s1[i]=(s1[i-1]+d[i-1])%P;
	f[m+1]=1;
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
			s2[j]=(s2[j-1]+1ll*d[j-1]*f[j])%P;
		for (int j=1; j<=m; j++)
			g[j+1]=(g[j]+(1ll*(f[m+1]-f[m-j+1]+P)*s1[j]-s2[j]+P)%P*d[m-j])%P;
		swap(f, g);
	}
	printf("%d\n", f[m+1]);
	return 0;
}
