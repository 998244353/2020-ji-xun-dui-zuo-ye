#include <cstdio>
#include <cctype>
#include <cstring>
const int MAXM=510;
const int MAXS=66000;
const int P=1E9+7;
int n, m;
char a[MAXM];
int f[MAXM][MAXS];
int t1[MAXS], t2[MAXS];
void DWT(int* a, char c, int ty)
{
	if (c=='|')
	{
		if (ty==1)
		{
			for (int i=0; i<16; i++)
				for (int s=0; s<1<<16; s++)
					if (s&1<<i) a[s]=(a[s]+a[s^1<<i])%P;
		}
		else
		{
			for (int i=0; i<16; i++)
				for (int s=(1<<16)-1; s>=0; s--)
					if (s&1<<i) a[s]=(a[s]-a[s^1<<i]+P)%P;
		}
	}
	else
	{
		if (ty==1)
		{
			for (int i=0; i<16; i++)
				for (int s=(1<<16)-1; s>=0; s--)
					if (!(s&1<<i)) a[s]=(a[s]+a[s^1<<i])%P;
		}
		else
		{
			for (int i=0; i<16; i++)
				for (int s=0; s<1<<16; s++)
					if (!(s&1<<i)) a[s]=(a[s]-a[s^1<<i]+P)%P;
		}
	}
}
int calc(char c)
{
	int s=0;
	if (isupper(c))
	{
		for (int i=0; i<16; i++)
			if (i&1<<c-'A') s|=1<<i;
	}
	else
	{
		for (int i=0; i<16; i++)
			if (!(i&1<<c-'a')) s|=1<<i;
	}
	return s;
}
void solve(int l, int r)
{
	if (l==r)
	{
		m++;
		if (a[l]!='?') f[m][calc(a[l])]++;
		else
			for (int i=0; i<4; i++)
				f[m][calc('A'+i)]++, f[m][calc('a'+i)]++;
		return;
	}
	int p, lc, rc;
	for (int i=l, t=0; i<=r; i++)
		if (a[i]=='(') t++;
		else if (a[i]==')') t--;
		else if (t==0) p=i;
	solve(l+1, p-2), lc=m;
	solve(p+2, r-1), rc=m;
	m++;
	if (a[p]!='?')
	{
		DWT(f[lc], a[p], 1), DWT(f[rc], a[p], 1);
		for (int s=0; s<1<<16; s++)
			f[m][s]=1ll*f[lc][s]*f[rc][s]%P;
		DWT(f[m], a[p], -1);
	}
	else
	{
		memcpy(t1, f[lc], sizeof t1);
		memcpy(t2, f[rc], sizeof t2);
		DWT(f[lc], '|', 1), DWT(f[rc], '|', 1);
		for (int s=0; s<1<<16; s++)
			f[m][s]=1ll*f[lc][s]*f[rc][s]%P;
		DWT(f[m], '|', -1);
		DWT(f[m], '&', 1);
		DWT(t1, '&', 1), DWT(t2, '&', 1);
		for (int s=0; s<1<<16; s++)
			f[m][s]=(f[m][s]+1ll*t1[s]*t2[s])%P;
		DWT(f[m], '&', -1);
	}
}
int pos[MAXM], val[MAXM];
bool check(int s)
{
	for (int i=1; i<=n; i++)
		if (s>>pos[i]&1^val[i]) return 0;
	return 1;
}
int main()
{
//	freopen("CF582E.in", "r", stdin);
//	freopen("CF582E.out", "w", stdout);
	scanf("%s%d", a+1, &n);
	for (int i=1; i<=n; i++)
	{
		for (int j=0, x; j<4; j++)
			scanf("%d", &x), pos[i]|=x<<j;
		scanf("%d", &val[i]);
	}
	solve(1, strlen(a+1));
	int ans=0;
	for (int s=0; s<=1<<16; s++)
		if (check(s)) ans=(ans+f[m][s])%P;
	printf("%d\n", ans);
	return 0;
}
