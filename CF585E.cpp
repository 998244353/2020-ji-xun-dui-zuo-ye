#include <cstdio>
const int MAXN=5E5+5;
const int MAXW=1E7+5;
const int W=1E7, P=1E9+7;
bool mark[MAXW];
int pw[MAXN], pri[MAXW/10], mu[MAXW];
int f[MAXW], g[MAXW];
int main()
{
//	freopen("CF585E.in", "r", stdin);
//	freopen("CF585E.out", "w", stdout);
	int n, m=0;
	scanf("%d", &n);
	mu[1]=1;
	for (int i=2; i<=W; i++)
	{
		if (!mark[i]) pri[++m]=i, mu[i]=-1;
		for (int j=1; i*pri[j]<=W; j++)
		{
			mark[i*pri[j]]=1;
			if (i%pri[j]==0)
				{ mu[i*pri[j]]=0; break; }
			mu[i*pri[j]]=-mu[i];
		}
	}
	pw[0]=1;
	for (int i=1, x; i<=n; i++)
	{
		scanf("%d", &x), f[x]++;
		pw[i]=(pw[i-1]+pw[i-1])%P;
	}
	for (int i=1; i<=m; i++)
		for (int j=W/pri[i]; j>=1; j--)
			f[j]=(f[j]+f[pri[i]*j])%P;
	for (int i=1; i<=W; i++)
		g[i]=pw[f[i]]-1, f[i]=(f[i]*mu[i]+P)%P;
	for (int i=1; i<=m; i++)
	{
		for (int j=1; pri[i]*j<=W; j++)
			f[pri[i]*j]=(f[pri[i]*j]+f[j])%P;
		for (int j=1; pri[i]*j<=W; j++)
			g[j]=(g[j]-g[pri[i]*j]+P)%P;
	}
	int ans=0;
	for (int i=2; i<=W; i++)
		ans=(ans+1ll*f[i]*g[i])%P;
	printf("%d\n", ans);
	return 0;
}
