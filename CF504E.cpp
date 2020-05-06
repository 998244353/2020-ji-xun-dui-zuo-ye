#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MAXN=330000;
const int MAXB=19;
const int BASE=rng()%19260817+31;
const int MOD1=998244353;
const int MOD2=1004535809;
struct Hash
{
	int a, b;
	Hash() {}
	Hash(int x): a(x), b(x) {}
	Hash(int x, int y): a(x), b(y) {}
	bool operator == (const Hash& rhs) const
	{
		return a==rhs.a&&b==rhs.b;
	}
	friend Hash operator + (const Hash& lhs, const Hash& rhs)
	{
		return Hash(lhs.a+rhs.a<MOD1?lhs.a+rhs.a:lhs.a+rhs.a-MOD1,
		            lhs.b+rhs.b<MOD2?lhs.b+rhs.b:lhs.b+rhs.b-MOD2);
	}
	friend Hash operator - (const Hash& lhs, const Hash& rhs)
	{
		return Hash(lhs.a-rhs.a>=0?lhs.a-rhs.a:lhs.a-rhs.a+MOD1,
		            lhs.b-rhs.b>=0?lhs.b-rhs.b:lhs.b-rhs.b+MOD2);
	}
	friend Hash operator * (const Hash& lhs, const Hash& rhs)
	{
		return Hash(1ll*lhs.a*rhs.a%MOD1, 1ll*lhs.b*rhs.b%MOD2);
	}
};
int qpow(int n, int p)
{
	int k=p-2, r=1;
	while (k)
	{
		if (k&1) r=1ll*r*n%p;
		n=1ll*n*n%p; k>>=1;
	}
	return r;
}
const Hash IBASE=Hash(qpow(BASE, MOD1), qpow(BASE, MOD2));
char s[MAXN];
Hash pw[MAXN], ipw[MAXN];
Hash h1[MAXN], h2[MAXN];
int fa[MAXN][MAXB], dep[MAXN];
int len[MAXN], son[MAXN], fir[MAXN];
int hb[MAXN];
vector<int> g[MAXN], q[MAXN], p[MAXN];
int read()
{
	int x=0; char ch=0;
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x;
}
void dfs1(int u, int f, int d)
{
	len[u]=1, son[u]=0;
	fa[u][0]=f, dep[u]=d;
	for (int i=1; i<=18; i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	h1[u]=h1[f]+(s[u]-'a'+1)*pw[d];
	h2[u]=h2[f]*BASE+(s[u]-'a'+1);
	for (int v:g[u])
		if (v!=f)
		{
			dfs1(v, u, d+1);
			if (len[v]+1>len[u])
				len[u]=len[v]+1, son[u]=v;
		}
}
void dfs2(int u, int t)
{
	fir[u]=t;
	if (u==t)
	{
		int v=u;
		for (int i=1; i<=len[u]; i++)
			q[u].push_back(v), v=son[v];
		v=fa[u][0];
		for (int i=1; i<=len[u]; i++)
			p[u].push_back(v), v=fa[v][0];
	}
	for (int v:g[u])
		if (v!=fa[u][0])
			if (v==son[u]) dfs2(v, t);
			else dfs2(v, v);
}
int lca(int u, int v)
{
	if (dep[u]<dep[v]) swap(u, v);
	for (int i=18; i>=0; i--)
		if (dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if (u==v) return u;
	for (int i=18; i>=0; i--)
		if (fa[u][i]!=fa[v][i]) u=fa[u][i], v=fa[v][i];
	return fa[u][0];
}
int kth(int u, int k)
{
	if (k==0) return u;
	u=fa[u][hb[k]], k-=1<<hb[k];
	if (dep[u]-k>=dep[fir[u]]) return q[fir[u]][dep[u]-k-dep[fir[u]]];
	return p[fir[u]][k-dep[u]+dep[fir[u]]-1];
}
Hash calc(int u, int v, int w, int k)
{
	if (k<=dep[u]-dep[w]) return (h1[u]-h1[kth(u, k)])*ipw[dep[u]-k+1];
	return (h1[u]-h1[w])*ipw[dep[w]+1]*pw[k-dep[u]+dep[w]]
	+h2[kth(v, dep[u]+dep[v]-2*dep[w]+1-k)]-h2[fa[w][0]]*pw[k-dep[u]+dep[w]];
}
int main()
{
//	freopen("CF504E.in", "r", stdin);
//	freopen("CF504E.out", "w", stdout);
	int n, m;
	scanf("%d%s", &n, s+1);
	for (int i=1; i<n; i++)
	{
		int u=read(), v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	pw[0]=1, ipw[0]=1;
	for (int i=1; i<=n; i++)
		pw[i]=pw[i-1]*BASE, ipw[i]=ipw[i-1]*IBASE;
	dfs1(1, 0, 1), dfs2(1, 1);
	for (int i=1, t=hb[0]=-1; i<=n; i++) hb[i]=t+=i>>t+1&1;
	scanf("%d", &m);
	while (m--)
	{
		int a=read(), b=read(), c=read(), d=read();
		int x=lca(a, b), y=lca(c, d);
		int l=0, r=min(dep[a]+dep[b]-2*dep[x]+1, dep[c]+dep[d]-2*dep[y]+1);
		while (l<r)
		{
			int mid=l+r+1>>1;
			if (calc(a, b, x, mid)==calc(c, d, y, mid)) l=mid;
			else r=mid-1;
		}
		printf("%d\n", l);
	}
	return 0;
}
