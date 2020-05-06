#include <cstdio>
#include <cstring>
const int MAXN=1100;
const int MAXD=55;
const int P=1E9+7;
namespace SAM
{
	struct Node
	{
		int nxt[10], par, len;
	} st[2*MAXN];
	int m, lst, root;
	int newNode(int l)
	{
		m++;
		memset(st[m].nxt, 0, sizeof st[m].nxt);
		st[m].par=0, st[m].len=l;
		return m;
	}
	void extend(int x)
	{
		int p=lst, np=newNode(st[p].len+1); lst=np;
		while (p&&!st[p].nxt[x]) st[p].nxt[x]=np, p=st[p].par;
		if (!p) st[np].par=root;
		else
		{
			int q=st[p].nxt[x];
			if (st[p].len+1==st[q].len) st[np].par=q;
			else
			{
				int nq=newNode(st[p].len+1);
				memcpy(st[nq].nxt, st[q].nxt, sizeof st[q].nxt);
				st[nq].par=st[q].par, st[q].par=st[np].par=nq;
				while (p&&st[p].nxt[x]==q) st[p].nxt[x]=nq, p=st[p].par;
			}
		}
	}
	void build(char* s)
	{
		m=0, lst=root=newNode(0);
		for (int i=0; s[i]; i++) extend(s[i]-'0');
	}
}
char s[MAXN], x[MAXD], y[MAXD];
int d, f[MAXD][2][2][2*MAXN][MAXD/2][2];
int dp(int k, int a, int b, int p, int l, int s)
{
	if (k==d) return s;
	int &ret=f[k][a][b][p][l][s];
	if (~ret) return ret;
	ret=0;
	int low=a?x[k]-'0':0, up=b?y[k]-'0':9;
	for (int i=low; i<=up; i++)
	{
		int q=0, t=0;
		if (!s)
		{
			q=p, t=l;
			while (q&&!SAM::st[q].nxt[i])
				q=SAM::st[q].par, t=SAM::st[q].len;
			if (!q) q=SAM::root, t=0;
			else q=SAM::st[q].nxt[i], t++;
		}
		ret=(ret+dp(k+1, a&i==low, b&i==up, q, t, s|t>=d/2))%P;
	}
	return ret;
}
int main()
{
//	freopen("CF585F.in", "r", stdin);
//	freopen("CF585F.out", "w", stdout);
	scanf("%s%s%s", s, x, y);
	d=strlen(x);
	SAM::build(s);
	memset(f, -1, sizeof f);
	printf("%d\n", dp(0, 1, 1, SAM::root, 0, 0));
	return 0;
}
