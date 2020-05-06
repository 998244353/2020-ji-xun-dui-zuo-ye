#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
const int MAXN=110000;
const int B=1000;
int n, q;
inline int lb(int x) { return x&-x; }
struct BIT
{
	int s[MAXN];
	void add(int x, int k)
	{
		while (x<=n) s[x]+=k, x+=lb(x);
	}
	int sum(int x)
	{
		int r=0;
		while (x>0) r+=s[x], x-=lb(x);
		return r;
	}
} bit;
struct Query
{
	int l, r, k;
} a[MAXN];
string s[MAXN];
int cnt, root;
int nxt[MAXN][26], fail[MAXN];
vector<int> pos[MAXN], g[MAXN];
vector<int> qry[MAXN], qwq[MAXN];
int op[MAXN], cl[MAXN], dfn;
int pre[MAXN]; ll sum[MAXN], ans[MAXN];
int insert(int x)
{
	int p=root;
	for (char c:s[x])
	{
		int &t=nxt[p][c-'a'];
		if (!t) t=++cnt; p=t;
	}
	pos[p].push_back(x);
	return p;
}
void build()
{
	queue<int> que; que.push(root);
	while (!que.empty())
	{
		int p=que.front(); que.pop();
		for (int i=0; i<26; i++)
		{
			int q=nxt[p][i], t=fail[p];
			if (q)
			{
				while (t&&!nxt[t][i]) t=fail[t];
				fail[q]=t?nxt[t][i]:root;
				g[fail[q]].push_back(q);
				que.push(q);
			}
		}
	}
}
void addqry(int x)
{
	int p=root;
	for (char c:s[a[x].k])
		p=nxt[p][c-'a'], qry[p].push_back(x);
}
void addpre(int x)
{
	int p=root;
	for (char c:s[x])
		p=nxt[p][c-'a'], pre[op[p]]++;
}
void dfs(int p)
{
	op[p]=++dfn;
	for (int x:pos[p]) bit.add(x, 1);
	for (int x:qry[p])
		ans[x]+=bit.sum(a[x].r)-bit.sum(a[x].l-1);
	for (int q:g[p]) dfs(q);
	for (int x:pos[p]) bit.add(x, -1);
	cl[p]=dfn;
}
int main()
{
//	freopen("CF587F.in", "r", stdin);
//	freopen("CF587F.out", "w", stdout);
	scanf("%d%d", &n, &q);
	root=cnt=1;
	for (int i=1; i<=n; i++)
		cin>>s[i], insert(i);
	build();
	for (int i=1; i<=q; i++)
	{
		scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].k);
		if (s[a[i].k].size()<=B) addqry(i);
		else qwq[a[i].k].push_back(i);
	}
	dfs(root);
	for (int i=1; i<=n; i++)
		if (s[i].size()>B)
		{
			for (int i=1; i<=cnt; i++) pre[i]=0;
			for (int i=1; i<=n; i++) sum[i]=0;
			addpre(i);
			for (int i=1; i<=cnt; i++) pre[i]+=pre[i-1];
			for (int i=1; i<=cnt; i++)
				for (int x:pos[i])
					sum[x]+=pre[cl[i]]-pre[op[i]-1];
			for (int i=1; i<=n; i++) sum[i]+=sum[i-1];
			for (int x:qwq[i]) ans[x]=sum[a[x].r]-sum[a[x].l-1];
		}
	for (int i=1; i<=q; i++) printf("%lld\n", ans[i]);
	return 0;
}
