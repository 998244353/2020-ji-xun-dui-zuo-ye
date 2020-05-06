#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN=110000;
struct Edge
{
	int to, val;
	Edge(int v, int w): to(v), val(w) {}
};
vector<Edge> g[MAXN];
ll dis[MAXN], mx[MAXN];
int p[MAXN], fa[MAXN];
namespace dsu
{
	int f[MAXN], h[MAXN], sz[MAXN];
	void init(int n)
	{
		for (int i=1; i<=n; i++)
			f[i]=i, h[i]=sz[i]=1;
	}
	int getf(int x)
	{
		if (x==f[x]) return x;
		return f[x]=getf(f[x]);
	}
	void merge(int u, int v)
	{
		int x=getf(u), y=getf(v);
		if (x==y) return;
		if (h[x]<h[y]) f[x]=y, sz[y]+=sz[x];
		else
		{
			f[y]=x, sz[x]+=sz[y];
			if (h[x]==h[y]) h[x]++;
		}
	}
}
void getdis(int u, int f)
{
	for (Edge e:g[u])
	{
		int v=e.to;
		if (v!=f)
		{
			dis[v]=dis[u]+e.val;
			getdis(v, u);
		}
	}
}
void dfs(int u, int f)
{
	fa[u]=f;
	for (Edge e:g[u])
		if (e.to!=f) dfs(e.to, u);
}
int main()
{
//	freopen("CF516D.in", "r", stdin);
//	freopen("CF516D.out", "w", stdout);
	int n, q;
	scanf("%d", &n);
	for (int i=1; i<n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[u].push_back(Edge(v, w));
		g[v].push_back(Edge(u, w));
	}
	int x;
	dis[1]=0, getdis(1, 0), x=0;
	for (int i=1; i<=n; i++)
		if (dis[i]>dis[x]) x=i;
	dis[x]=0, getdis(x, 0), x=0;
	for (int i=1; i<=n; i++)
	{
		mx[i]=dis[i];
		if (dis[i]>dis[x]) x=i;
	}
	dis[x]=0, getdis(x, 0);
	for (int i=1; i<=n; i++)
		mx[i]=max(mx[i], dis[i]), p[i]=i;
	sort(p+1, p+n+1, [](int a, int b){ return mx[a]<mx[b]; });
	dfs(p[1], 0);
	scanf("%d", &q);
	while (q--)
	{
		ll l; scanf("%lld", &l);
		dsu::init(n);
		int ans=0;
		for (int i=n, j=n; i>=1; i--)
		{
			while (mx[p[j]]-mx[p[i]]>l)
				dsu::sz[dsu::getf(p[j--])]--;
			ans=max(ans, dsu::sz[dsu::getf(p[i])]);
			if (fa[p[i]]) dsu::merge(p[i], fa[p[i]]);
		}
		printf("%d\n", ans);
	}
	return 0;
}

