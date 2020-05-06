#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
/* point template begin */
struct Point { int x, y; };
ll crossdet(int x1, int y1, int x2, int y2)
{
	return 1ll*x1*y2-1ll*x2*y1;
}
ll cross(Point a, Point b, Point c)
{
	return crossdet(b.x-a.x, b.y-a.y, c.x-a.x, c.y-a.y);
}
ll dotdet(int x1, int y1, int x2, int y2)
{
	return 1ll*x1*x2+1ll*y1*y2;
}
ll dot(Point a, Point b, Point c)
{
	return dotdet(b.x-a.x, b.y-a.y, c.x-a.x, c.y-a.y);
}
/* point template end */
const int MAXM=10, MAXN=1100;
int n, m;
Point a[MAXM], b[MAXN];
vector<int> p[MAXM][MAXN];
int d[MAXM], c;
bool vis[MAXN];
vector<int> book;
void dfs(int u)
{
	c++; vis[u]=1; book.push_back(u);
	for (int v:p[d[c]][u])
		if (!vis[v])
		{
			dfs(v);
			if (c>m) return;
		}
}
int main()
{
//	freopen("CF698D.in", "r", stdin);
//	freopen("CF698D.out", "w", stdout);
	scanf("%d%d", &m, &n);
	for (int i=1; i<=m; i++)
		scanf("%d%d", &a[i].x, &a[i].y);
	for (int i=1; i<=n; i++)
		scanf("%d%d", &b[i].x, &b[i].y);
	for (int i=1; i<=m; i++)
		for (int j=1; j<=n; j++)
			for (int k=1; k<=n; k++)
				if (cross(a[i], b[j], b[k])==0&&dot(b[k], a[i], b[j])<0)
					p[i][j].push_back(k);
	int ans=0;
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++) d[j]=j;
		do
		{
			book.clear();
			c=0, dfs(i);
			for (int k:book) vis[k]=0;
			if (c<=m) { ans++; break; }
		} while (next_permutation(d+1, d+m+1));
	}
	printf("%d\n", ans);
	return 0;
}

