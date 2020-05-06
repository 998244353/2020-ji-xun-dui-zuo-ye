#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;
const int MAXM=30;
const int INF=1E9;
namespace MF
{
	struct Edge
	{
		int from, to, cap, flow;
		Edge(int u, int v, int c, int f):
			from(u), to(v), cap(c), flow(f) {}
	};
	int n, s, t, flow;
	vector<Edge> edges;
	vector<int> g[MAXM];
	int h[MAXM], cur[MAXM];
	void init(int v, int a, int b)
	{
		n=v, s=a, t=b, flow=0;
		edges.clear();
		for (int i=1; i<=n; i++) g[i].clear();
	}
	void addEdge(int from, int to, int cap)
	{
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));
		g[from].push_back(edges.size()-2);
		g[to].push_back(edges.size()-1);
	}
	bool bfs()
	{
		queue<int> q;
		for (int i=1; i<=n; i++) cur[i]=h[i]=0;
		h[s]=1, q.push(s);
		while (!q.empty())
		{
			int u=q.front(); q.pop();
			for (int i=0; i<g[u].size(); i++)
			{
				Edge e=edges[g[u][i]];
				if (e.cap>e.flow&&!h[e.to])
					h[e.to]=h[u]+1, q.push(e.to);
			}
		}
		return h[t];
	}
	int dfs(int u, int f)
	{
		if (u==t) return f;
		for (int &i=cur[u]; i<g[u].size(); i++)
		{
			Edge &e=edges[g[u][i]];
			if (e.cap>e.flow&&h[e.to]==h[u]+1)
			{
				int d=dfs(e.to, min(f, e.cap-e.flow));
				if (d>0)
				{
					e.flow+=d;
					edges[g[u][i]^1].flow-=d;
					return d;
				}
			}
		}
		return 0;
	}
	void Dinic()
	{
		while (bfs())
			while (int f=dfs(s, INF)) flow+=f;
	}
}
int n, m;
int a[MAXM], b[MAXM];
int c[MAXM][MAXM], p[MAXM], q[MAXM];
pair<int, int> d[MAXM];
bool used[MAXM]; int cnt[MAXM];
bool t[MAXM][MAXM];
void work()
{
	for (int i=1; i<=m; i++) used[i]=0;
	for (int i=1; i<=m-2; i++) cnt[a[i]]++;
	for (int i=1; i<=m; i++)
		for (int j=i; j<=m; j++) t[i][j]=0;
	for (int i=1; i<=m-2; i++)
	{
		for (int j=1; j<=m; j++)
			if (!used[j]&&!cnt[j])
			{
				if (a[i]<j) t[a[i]][j]=1;
				else t[j][a[i]]=1;
				used[j]=1; break;
			}
		cnt[a[i]]--;
	}
	for (int i=1; i<=m; i++)
		if (!used[i]) { t[i][m]=1; break; }
	int l=m*(m+1)/2;
	MF::init(l+m+2, l+m+1, l+m+2);
	for (int i=1; i<=l; i++)
	{
		int u=d[i].first, v=d[i].second;
		if (t[u][v]>c[u][v]) return;
		MF::addEdge(MF::s, i, c[u][v]-t[u][v]);
		MF::addEdge(i, u+l, INF);
		MF::addEdge(i, v+l, INF);
	}
	for (int i=1; i<=m; i++)
		MF::addEdge(i+l, MF::t, b[i]-1);
	MF::Dinic();
	if (MF::flow==n-m)
	{
		for (int i=1; i<=m; i++)
			for (int j=i; j<=m; j++)
				if (t[i][j])
					printf("%d %d\n", p[i], p[j]);
		for (int i=1; i<=m; i++) q[i]=p[i];
		for (MF::Edge e:MF::edges)
			if (e.cap==INF) while (e.flow--)
				printf("%d %d\n", p[d[e.from].first^d[e.from].second^e.to-l], ++q[e.to-l]);
		exit(0);
	}
}
void dfs(int k)
{
	if (k==m-1) { work(); return; }
	for (int i=1; i<=m; i++)
		a[k]=i, dfs(k+1);
}
int main()
{
//	freopen("CF611H.in", "r", stdin);
//	freopen("CF611H.out", "w", stdout);
	scanf("%d", &n);
	p[1]=1;
	for (m=1; p[m]*10<=n; m++)
		b[m]=p[m]*9, p[m+1]=p[m]*10;
	b[m]=n-p[m]+1;
	for (int i=1; i<n; i++)
	{
		char s[10]; int u, v;
		scanf("%s", s), u=strlen(s);
		scanf("%s", s), v=strlen(s);
		if (u>v) swap(u, v); c[u][v]++;
	}
	for (int i=1, l=0; i<=m; i++)
		for (int j=i; j<=m; j++)
			d[++l]=make_pair(i, j);
	if (m==1)
		for (int i=1; i<n; i++)
			printf("%d %d\n", i, i+1);
	else dfs(1), puts("-1");
	return 0;
}
