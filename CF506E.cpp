#include <cstdio>
#include <cstring>
const int MAXN=205;
const int MAXM=305;
const int P=10007;
struct Matrix
{
	int n, m, a[MAXM][MAXM];
	Matrix(int r, int c): n(r), m(c)
	{
		memset(a, 0, sizeof a);
	}
	Matrix operator * (const Matrix& b)
	{
		Matrix c(n, b.m);
		for (int i=1; i<=n; i++)
			for (int k=i; k<=m; k++)
				for (int j=k; j<=b.m; j++)
					c.a[i][j]=(c.a[i][j]+a[i][k]*b.a[k][j])%P;
		return c;
	}
	Matrix qpow(int k) const
	{
		Matrix s=Matrix(n, m), t=*this;
		for (int i=1; i<=n; i++) s.a[i][i]=1;
		while (k)
		{
			if (k&1) s=s*t;
			t=t*t; k>>=1;
		}
		return s;
	}
};
int n, l;
char s[MAXN];
int f[MAXN][MAXN][MAXN];
int main()
{
//	freopen("CF506E.in", "r", stdin);
//	freopen("CF506E.out", "w", stdout);
	scanf("%s%d", s+1, &l);
	l+=n=strlen(s+1);
	f[1][n][0]=1;
	for (int d=n; d>=1; d--)
		for (int i=1; i+d-1<=n; i++)
		{
			int j=i+d-1;
			if (s[i]!=s[j])
			{
				for (int k=n-1; k>=1; k--) f[i][j][k]=f[i][j][k-1];
				f[i][j][0]=0;
				for (int k=0; k<n; k++)
				{
					f[i+1][j][k]=(f[i+1][j][k]+f[i][j][k])%P;
					f[i][j-1][k]=(f[i][j-1][k]+f[i][j][k])%P;
				}
			}
			else
				for (int k=0; k<n; k++)
					f[i+1][j-1][k]=(f[i+1][j-1][k]+f[i][j][k])%P;
		}
	for (int i=1; i<=n+1; i++)
		for (int j=0; j<=n; j++)
			for (int k=0; k<n; k++)
			{
				if (j<i) f[0][0][k]=(f[0][0][k]+f[i][j][k])%P;
				if (j==i+1&&s[i]==s[j]) f[n+1][n+1][k]=(f[n+1][n+1][k]+f[i][j][k])%P;
			}
	int m=n+(n+1)/2;
	Matrix v(1, m), w(m, m);
	for (int i=1; i<n; i++)
	{
		w.a[i][i]=24;
		if (i!=n-1) w.a[i][i+1]=1;
	}
	for (int i=n; i<m; i++)
		w.a[i][i]=25, w.a[i][i+1]=1;
	w.a[m][m]=26;
	for (int i=1; i<n; i++)
		w.a[i][m-(n-i+1)/2]=f[0][0][i];
	v.a[1][1]=1, v.a[1][n]=f[0][0][0];
	int ans=(v*w.qpow((l+1)/2)).a[1][m];
	if (l&1)
	{
		w.a[m][m]=0;
		for (int i=1; i<n; i++)
			w.a[i][m-(n-i+1)/2]=f[n+1][n+1][i];
		v.a[1][n]=f[n+1][n+1][0];
		ans=(ans-(v*w.qpow((l+1)/2)).a[1][m]+P)%P;
	}
	printf("%d\n", ans);
	return 0;
}
