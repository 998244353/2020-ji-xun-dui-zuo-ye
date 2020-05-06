#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN=660000;
namespace LFT
{
	struct Node
	{
		int ls, rs, dis;
		ll val, add; int pos;
	} tr[MAXN];
	int root[MAXN];
	void update(int x, ll k)
	{
		tr[x].val+=k, tr[x].add+=k;
	}
	void pushdown(int x)
	{
		if (tr[x].add)
		{
			if (tr[x].ls) update(tr[x].ls, tr[x].add);
			if (tr[x].rs) update(tr[x].rs, tr[x].add);
			tr[x].add=0;
		}
	}
	int merge(int x, int y)
	{
		if (!x||!y) return x|y;
		if (tr[x].val>tr[y].val) swap(x, y);
		pushdown(x);
		tr[x].rs=merge(tr[x].rs, y);
		if (tr[tr[x].ls].dis<tr[tr[x].rs].dis)
			swap(tr[x].ls, tr[x].rs);
		tr[x].dis=tr[tr[x].rs].dis+1;
		return x;
	}
	int pop(int x)
	{
		pushdown(x);
		return merge(tr[x].ls, tr[x].rs);
	}
}
using namespace LFT;
vector<int> g[MAXN];
int dep[MAXN];
ll dp[MAXN];
ll dfs(int u, int f)
{
	dep[u]=dep[f]+1; ll sum=0;
	for (int v:g[u])
		if (v!=f)
		{
			if (dfs(v, u)==-1) return -1;
			sum+=dp[v];
			update(root[v], -dp[v]);
			root[u]=merge(root[u], root[v]);
		}
	if (u==1) return sum;
	update(root[u], sum);
	while (root[u]&&dep[tr[root[u]].pos]>=dep[u])
		root[u]=pop(root[u]);
	if (!root[u]) return -1;
	dp[u]=tr[root[u]].val;
	return 0;
}
int main()
{
//	freopen("CF671D.in", "r", stdin);
//	freopen("CF671D.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i=1; i<n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int tot=n;
	for (int i=1; i<=m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		tr[++tot].val=w, tr[tot].pos=v;
		root[u]=merge(root[u], tot);
	}
	printf("%lld\n", dfs(1, 0));
	return 0;
}
