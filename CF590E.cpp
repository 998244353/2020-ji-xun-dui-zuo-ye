#include <cstdio>
#include <queue>
using namespace std;
const int MAXN=1600;
const int MAXM=10000005;
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
	vector<int> g[MAXN];
	int h[MAXN], cur[MAXN];
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
int g[MAXN][MAXN];
namespace ACAM
{
	struct Node
	{
		int val, nxt;
		Node() {}
		Node(int a, int b): val(a), nxt(b) {}
	} a[2*MAXM];
	int nxt[MAXM][2], fail[MAXM];
	int son[MAXM], pos[MAXM], end[MAXM];
	int cnt, root, tot;
	void insert(char* s, int d)
	{
		int p=root;
		for (int i=0; s[i]; i++)
		{
			int &t=nxt[p][s[i]-'a'];
			if (!t) t=++cnt; p=t;
			a[++tot]=Node(d, pos[p]), pos[p]=tot;
		}
		end[p]=d;
	}
	void build()
	{
		queue<int> que; que.push(root);
		while (!que.empty())
		{
			int p=que.front(); que.pop();
			for (int i=0; i<=1; i++)
			{
				int q=nxt[p][i], t=fail[p];
				if (q)
				{
					while (t&&!nxt[t][i]) t=fail[t];
					fail[q]=t?nxt[t][i]:root;
					a[++tot]=Node(q, son[fail[q]]), son[fail[q]]=tot;
					que.push(q);
				}
			}
		}
	}
	void bfs()
	{
		queue<pair<int, int>> que;
		que.push(make_pair(root, 0));
		while (!que.empty())
		{
			auto tmp=que.front(); que.pop();
			int p=tmp.first, k=tmp.second;
			for (int i=pos[p]; i; i=a[i].nxt)
			{
				int t=!end[p]||end[p]==a[i].val?k:end[p];
				if (t) g[a[i].val][t]=1;
			}
			if (end[p]) k=end[p];
			for (int i=son[p]; i; i=a[i].nxt)
				que.push(make_pair(a[i].val, k));
		}
	}
}
char s[MAXM];
int main()
{
//	freopen("CF590E.in", "r", stdin);
//	freopen("CF590E.out", "w", stdout);
	int n;
	scanf("%d", &n);
	ACAM::root=ACAM::cnt=1;
	for (int i=1; i<=n; i++)
		scanf("%s", s), ACAM::insert(s, i);
	ACAM::build();
	ACAM::bfs();
	for (int k=1; k<=n; k++)
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++)
				g[i][j]|=g[i][k]&g[k][j];
	MF::init(2*n+2, 2*n+1, 2*n+2);
	for (int i=1; i<=n; i++)
	{
		MF::addEdge(MF::s, i, 1);
		MF::addEdge(i+n, MF::t, 1);
	}
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			if (g[i][j]) MF::addEdge(i, j+n, INF);
	MF::Dinic();
	printf("%d\n", n-MF::flow);
	for (int i=1; i<=n; i++)
		if (MF::h[i]&&!MF::h[i+n]) printf("%d ", i);
	putchar('\n');
	return 0;
}
