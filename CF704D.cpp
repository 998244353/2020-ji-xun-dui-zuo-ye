#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const int MAXN=220000;
const int INF=1E9;
const ll LINF=1E18;
namespace MF
{
	struct Edge
	{
		int from, to; ll cap, flow;
		Edge(int u, int v, ll c, ll f):
			from(u), to(v), cap(c), flow(f) {}
	};
	int n, s, t; ll flow;
	vector<Edge> edges;
	vector<int> g[MAXN];
	int h[MAXN], cur[MAXN];
	void init(int v, int a, int b)
	{
		n=v, s=a, t=b, flow=0;
		edges.clear();
		for (int i=1; i<=n; i++) g[i].clear();
	}
	int addEdge(int from, int to, ll cap)
	{
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));
		g[from].push_back(edges.size()-2);
		g[to].push_back(edges.size()-1);
		return edges.size()-2;
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
	ll dfs(int u, ll f)
	{
		if (u==t) return f;
		for (int &i=cur[u]; i<g[u].size(); i++)
		{
			Edge &e=edges[g[u][i]];
			if (e.cap>e.flow&&h[e.to]==h[u]+1)
			{
				ll d=dfs(e.to, min(f, e.cap-e.flow));
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
			while (ll f=dfs(s, LINF)) flow+=f;
	}
}
namespace MFC
{
	int n, s, t;
	ll d[MAXN];
	void init(int v)
	{
		n=v, s=v+1, t=v+2;
		MF::init(n+2, s, t);
		for (int i=1; i<=n; i++) d[i]=0;
	}
	int addEdge(int from, int to, ll low, ll up)
	{
		if (low>up) puts("-1"), exit(0);
		d[from]-=low, d[to]+=low;
		return MF::addEdge(from, to, up-low);
	}
	bool getany()
	{
		ll sum=0;
		for (int i=1; i<=n; i++)
			if (d[i]>0) MF::addEdge(s, i, d[i]), sum+=d[i];
			else if (d[i]<0) MF::addEdge(i, t, -d[i]);
		MF::Dinic();
		return MF::flow==sum;
	}
	void getmax(int a, int b)
	{
		for (int i=0; i<MF::edges.size(); i++)
		{
			MF::Edge &e=MF::edges[i];
			if (e.from==b&&e.to==a)
			{
				MF::flow=e.flow;
				e.cap=e.flow=MF::edges[i^1].flow=0;
			}
			else if (e.from==s||e.to==t)
				e.cap=e.flow=MF::edges[i^1].flow=0;
		}
		MF::s=a, MF::t=b, MF::Dinic();
	}
}
int x[MAXN], y[MAXN];
int vx[MAXN], vy[MAXN], p, q;
int cx[MAXN], cy[MAXN];
int dx[MAXN], dy[MAXN];
int id[MAXN];
inline int posx(int k)
{
	return lower_bound(vx+1, vx+p+1, k)-vx;
}
inline int posy(int k)
{
	return lower_bound(vy+1, vy+q+1, k)-vy;
}
int main()
{
//	freopen("CF704D.in", "r", stdin);
//	freopen("CF704D.out", "w", stdout);
	int n, m, r, b;
	scanf("%d%d%d%d", &n, &m, &r, &b);
	for (int i=1; i<=n; i++)
	{
		scanf("%d%d", &x[i], &y[i]);
		vx[++p]=x[i], vy[++q]=y[i];
	}
	sort(vx+1, vx+p+1), p=unique(vx+1, vx+p+1)-vx-1;
	sort(vy+1, vy+q+1), q=unique(vy+1, vy+q+1)-vy-1;
	for (int i=1; i<=p; i++) cx[i]=0, dx[i]=INF;
	for (int i=1; i<=q; i++) cy[i]=0, dy[i]=INF;
	for (int i=1; i<=m; i++)
	{
		int t, l, k;
		scanf("%d%d%d", &t, &l, &k);
		if (t==1)
		{
			int u=posx(l);
			if (vx[u]==l) dx[u]=min(dx[u], k);
		}
		else
		{
			int u=posy(l);
			if (vy[u]==l) dy[u]=min(dy[u], k);
		}
	}
	MFC::init(p+q+2);
	int s=p+q+1, t=p+q+2;
	MFC::addEdge(t, s, 0, INF);
	for (int i=1; i<=n; i++)
	{
		int u=posx(x[i]), v=posy(y[i]);
		id[i]=MFC::addEdge(u, v+p, 0, 1);
		cx[u]++, cy[v]++;
	}
	for (int i=1; i<=p; i++)
		MFC::addEdge(s, i, (cx[i]-dx[i]+1)/2, (cx[i]+dx[i])/2);
	for (int i=1; i<=q; i++)
		MFC::addEdge(i+p, t, (cy[i]-dy[i]+1)/2, (cy[i]+dy[i])/2);
	if (!MFC::getany()) puts("-1");
	else
	{
		MFC::getmax(s, t);
		ll ans=0; string ret;
		for (int i=1; i<=n; i++)
		{
			bool t=MF::edges[id[i]].flow^(b<r);
			if (t) ans+=r, ret+='r';
			else ans+=b, ret+='b';
		}
		cout<<ans<<endl<<ret<<endl;
	}
	return 0;
}
