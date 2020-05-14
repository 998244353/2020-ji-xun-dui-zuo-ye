#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=220000;
vector<int> operator + (const vector<int>& lhs, const vector<int>& rhs)
{
	vector<int> ret;
	ret.insert(ret.end(), lhs.begin(), lhs.end());
	ret.insert(ret.end(), rhs.begin(), rhs.end());
	return ret;
}
void print(const vector<int>& vec)
{
	printf("%d", (int)vec.size());
	for (int x: vec) printf(" %d", x);
	putchar('\n');
}
vector<int> G[MAXN], T[MAXN];
int fa[MAXN][18], dep[MAXN];
int dfn[MAXN], val[MAXN];
int lca(int u, int v)
{
	if (dep[u]<dep[v]) swap(u, v);
	for (int i=17; i>=0; i--)
		if (dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if (u==v) return u;
	for (int i=17; i>=0; i--)
		if (fa[u][i]!=fa[v][i]) u=fa[u][i], v=fa[v][i];
	return fa[u][0];
}
vector<int> getpath(int u, int v)
{
	vector<int> ret;
	int w=lca(u, v);
	while (u!=w) ret.push_back(u), u=fa[u][0];
	ret.push_back(w); int t=ret.size();
	while (v!=w) ret.push_back(v), v=fa[v][0];
	reverse(ret.begin()+t, ret.end());
	return ret;
}
void dfs1(int u)
{
	static int dfc=0;
	dfn[u]=++dfc;
	for (int i=1; i<18; i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for (int v: G[u])
		if (!dfn[v])
		{
			fa[v][0]=u, dep[v]=dep[u]+1;
			T[u].push_back(v);
			dfs1(v);
		}
		else if (dfn[v]<dfn[u]&&v!=fa[u][0])
			val[u]++, val[v]++, val[lca(u, v)]-=2;
}
void dfs2(int u)
{
	for (int v: T[u])
		dfs2(v), val[u]+=val[v];
}
void dfs3(int u, int w, int& x1, int& y1, int& x2, int& y2)
{
	for (int v: G[u])
		if (dfn[v]<=w&&v!=fa[u][0])
		{
			if (!x1) x1=u, y1=v;
			else x2=u, y2=v;
		}
	for (int v: T[u])
		dfs3(v, w, x1, y1, x2, y2);
}
int main()
{
//	freopen("CF521E.in", "r", stdin);
//	freopen("CF521E.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i=1; i<=m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i=1; i<=n; i++)
		if (!dfn[i])
		{
			dep[i]=1, dfs1(i);
			T[0].push_back(i);
		}
	dfs2(0);
	for (int i=1; i<=n; i++)
		if (val[i]>=2)
		{
			puts("YES");
			int x1=0, y1, x2, y2;
			dfs3(i, dfn[fa[i][0]], x1, y1, x2, y2);
			int a=lca(x1, x2), b=lca(y1, y2);
			if (y1==b) b=y2; else if (y2==b) b=y1;
			print(getpath(a, b));
			print(getpath(a, x1)+getpath(y1, b));
			print(getpath(a, x2)+getpath(y2, b));
			return 0;
		}
	puts("NO");
	return 0;
}
