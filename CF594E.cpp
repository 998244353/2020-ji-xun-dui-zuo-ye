#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=10000010;
int n, k, m;
char s[MAXN], t[MAXN];
char ans[MAXN], tmp[MAXN];
int p[MAXN], l[MAXN], z[MAXN];
int getpos1()
{
	for (int i=1; i<=p[m]; i++) s[i]=s[p[m]+i]=t[i];
	int i=1, j=1, k=0;
	while (i<=p[m]&&j<=p[m]&&k<p[m])
	{
		if (i==j) j++;
		else if (s[i+k]==s[j+k]) k++;
		else if (s[i+k]<s[j+k]) j+=k+1, k=0;
		else i+=k+1, k=0;
	}
	int ret=min(i, j)-1;
	return ret?ret:p[m];
}
int getpos2()
{
	for (int i=1; i<=p[m]; i++)
		s[i]=t[i], s[p[m]+i]=t[p[m]-i+1];
	z[1]=2*p[m];
	for (int i=2, l=0, r=0; i<=2*p[m]; i++)
	{
		if (i<=r) z[i]=min(z[i-l+1], r-i+1);
		while (i+z[i]<=2*p[m]&&s[i+z[i]]==s[z[i]+1]) z[i]++;
		if (i+z[i]-1>r) l=i, r=i+z[i]-1;
	}
	int d=p[m];
	for (int i=p[m]-1; i>=1; i--)
	{
		int len=z[2*p[m]-d+1];
		if (len<d-i)
		{
			if (t[d-len]<t[len+1]) d=i;
		}
		else
		{
			len=z[d-i+1];
			if (len<i&&t[len+1]<t[d-i+1+len]) d=i;
		}
	}
	return d;
}
bool check(int k)
{
	for (int i=p[k-1]+1; i<=p[m]; i++)
		if (t[i]!=t[i-p[k-1]+p[k-2]])
			return t[i]<t[i-p[k-1]+p[k-2]];
	for (int i=p[k-2]+1; i<=p[k-1]; i++)
		if (t[i]!=t[i+p[k-1]-p[k-2]])
			return t[i]<t[i+p[k-1]-p[k-2]];
	return 0;
}
int getpos3()
{
	for (int i=m; i>=2; i--)
		if (check(i)) return p[i-1];
	return p[m];
}
int main()
{
//	freopen("CF594E.in", "r", stdin);
//	freopen("CF594E.out", "w", stdout);
	scanf("%s%d", s+1, &k);
	n=strlen(s+1);
	for (int i=1; i<=n; i++) t[i]=s[n-i+1];
	if (k==1)
	{
		puts(strcmp(s+1, t+1)<0?s+1:t+1);
		return 0;
	}
	for (int i=1; i<=n; )
	{
		int j=i, k;
		for (k=i+1; k<=n&&t[k]>=t[j]; k++)
			if (t[k]>t[j]) j=i; else j++;
		while (i<=j) i+=k-j;
		p[++m]=i-1, l[m]=k-j;
	}
	while (k>=3&&m)
	{
		for (int i=p[m-1]+1; i<=p[m]; i++) putchar(t[i]);
		k-=l[m]!=1||l[m-1]!=1, m--;
	}
	for (int i=1; i<=p[m]; i++) ans[i]=t[p[m]-i+1];
	
	int d=getpos1();
	for (int i=1; i<=p[m]-d; i++) tmp[i]=t[i+d];
	for (int i=p[m]-d+1; i<=p[m]; i++) tmp[i]=t[i-p[m]+d];
	if (strcmp(tmp+1, ans+1)<0)
		for (int i=1; i<=p[m]; i++) ans[i]=tmp[i];
	
	d=getpos2();
	for (int i=1; i<=p[m]-d; i++) tmp[i]=t[p[m]-i+1];
	for (int i=p[m]-d+1; i<=p[m]; i++) tmp[i]=t[i-p[m]+d];
	if (strcmp(tmp+1, ans+1)<0)
		for (int i=1; i<=p[m]; i++) ans[i]=tmp[i];
	
	d=getpos3();
	for (int i=1; i<=p[m]-d; i++) tmp[i]=t[i+d];
	for (int i=p[m]-d+1; i<=p[m]; i++) tmp[i]=t[p[m]-i+1];
	if (strcmp(tmp+1, ans+1)<0)
		for (int i=1; i<=p[m]; i++) ans[i]=tmp[i];
	
	puts(ans+1);
	return 0;
}
