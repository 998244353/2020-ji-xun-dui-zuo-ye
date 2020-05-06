#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=110000;
const int P=1E9+7;
vector<int> a[MAXN], b[MAXN];
vector<int> e[MAXN], p;
int g[MAXN][2][2], f[MAXN][2], c[2];
bool vis[MAXN];
inline void add(int& x, int y)
{
	x+=y; if (x>=P) x-=P;
}
void dfs(int u)
{
	p.push_back(u), vis[u]=1;
	for (int v:e[u])
		if (!vis[v]) dfs(v);
}
void dp(int l, int r)
{
	int t=p.size();
	for (int i=0; i<=t; i++)
		g[i][0][0]=g[i][0][1]=g[i][1][0]=g[i][1][1]=0;
	if (~l) g[0][0][l]=1;
	else g[0][0][0]=g[0][0][1]=1;
	int tmp=abs(a[p[0]][1]);
	if (!tmp||tmp!=abs(a[p[1]][0])&&tmp!=abs(a[p[1]][1]))
		swap(a[p[0]][0], a[p[0]][1]);
	for (int i=1; i<=t; i++)
	{
		if (i<t&&abs(a[p[i]][0])!=abs(a[p[i-1]][1]))
			swap(a[p[i]][0], a[p[i]][1]);
		for (int j=0; j<2; j++)
			for (int x=0; x<2; x++)
				for (int y=0; y<2; y++)
					add(g[i][j^(a[p[i-1]][0]<0^x|a[p[i-1]][1]<0^y)][y], g[i-1][j][x]);
	}
	for (int i=0; i<2; i++)
		if (~r) add(c[i], g[t][i][r]);
		else add(c[i], (g[t][i][0]+g[t][i][1])%P);
}
void solve(int u)
{
	p.clear(), dfs(u);
	if (p.size()==1)
	{
		int x=p.front();
		if (a[x].size()==1) c[0]=c[1]=1;
		else if (abs(a[x][0])!=abs(a[x][1])) c[0]=1, c[1]=3;
		else if (a[x][0]==a[x][1]) c[0]=c[1]=1;
		else c[0]=0, c[1]=2;
		return;
	}
	int rt=0;
	for (int x:p)
		if (e[x].size()==1) rt=x;
	c[0]=c[1]=0;
	if (rt)
	{
		for (int x:p) vis[x]=0;
		p.clear(), dfs(rt);
		int l=-1, r=-1;
		if (a[p.front()].size()==1)
			l=0, a[p.front()].push_back(0);
		if (a[p.back()].size()==1)
			r=0, a[p.back()].push_back(0);
		dp(l, r);
	}
	else dp(0, 0), dp(1, 1);
}
int main()
{
//	freopen("CF704C.in", "r", stdin);
//	freopen("CF704C.out", "w", stdout);
	int n, m, k=0;
	scanf("%d%d", &n, &m);
	for (int i=1; i<=n; i++)
	{
		int t; scanf("%d", &t);
		while (t--)
		{
			int x; scanf("%d", &x);
			a[i].push_back(x);
			b[abs(x)].push_back(i);
		}
	}
	f[0][0]=1;
	for (int i=1; i<=m; i++)
	{
		if (b[i].size()==2)
		{
			int x=b[i][0], y=b[i][1];
			e[x].push_back(y), e[y].push_back(x);
		}
		else if (b[i].empty()) add(f[0][0], f[0][0]);
	}
	for (int i=1; i<=n; i++)
		if (!vis[i])
		{
			solve(i); k++;
			for (int j=0; j<2; j++)
				f[k][j]=(1ll*f[k-1][j]*c[0]+1ll*f[k-1][j^1]*c[1])%P;
		}
	printf("%d\n", f[k][1]);
	return 0;
}
