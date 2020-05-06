#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=440000;
const int MAXS=26;
namespace SAM
{
	struct SegmentTree
	{
		struct Node
		{
			int ls, rs, val;
		} tr[MAXN<<5];
		int cnt;
		inline int newNode()
		{
			int x=++cnt;
			tr[x].ls=tr[x].rs=tr[x].val=0;
			return x;
		}
		void insert(int& x, int l, int r, int p)
		{
			if (!x) x=newNode(); tr[x].val++;
			if (l==r) return;
			int mid=l+r>>1;
			if (p<=mid) insert(tr[x].ls, l, mid, p);
			else insert(tr[x].rs, mid+1, r, p);
		}
		void merge(int x, int y, int& z)
		{
			z=newNode();
			if (!x||!y) { tr[z]=x?tr[x]:tr[y]; return; }
			tr[z].val=tr[x].val+tr[y].val;
			merge(tr[x].ls, tr[y].ls, tr[z].ls);
			merge(tr[x].rs, tr[y].rs, tr[z].rs);
		}
		int query(int x, int l, int r, int ql, int qr)
		{
			if (!x||l>qr||r<ql) return 0;
			if (ql<=l&&r<=qr) return tr[x].val;
			int mid=l+r>>1;
			return query(tr[x].ls, l, mid, ql, qr)
			      +query(tr[x].rs, mid+1, r, ql, qr);
		}
	} right;
	struct Node
	{
		int nxt[MAXS], par;
		int len, root, mx;
	} st[MAXN];
	int n, m, root, lst;
	int c[MAXN], d[MAXN], f[MAXN], g[MAXN];
	inline int newNode(int l)
	{
		int x=++m;
		memset(st[x].nxt, 0, sizeof st[x].nxt);
		st[x].len=l; st[x].root=0;
		return x;
	}
	void extend(int d, char c)
	{
		int x=c-'a';
		int p=lst, np=newNode(st[p].len+1); lst=np;
		right.insert(st[np].root, 1, n, d); st[np].mx=d;
		while (p&&!st[p].nxt[x]) st[p].nxt[x]=np, p=st[p].par;
		if (!p) { st[np].par=root; return; }
		int q=st[p].nxt[x]; if (st[q].len==st[p].len+1) { st[np].par=q; return; }
		int nq=newNode(st[p].len+1); memcpy(st[nq].nxt, st[q].nxt, sizeof st[q].nxt);
		st[nq].par=st[q].par; st[np].par=st[q].par=nq;
		while (p&&st[p].nxt[x]==q) st[p].nxt[x]=nq, p=st[p].par;
	}
	void build(char* s, int l)
	{
		n=l; m=0; st[0].len=-1; lst=root=newNode(0); right.cnt=0;
		for (int i=1; i<=n; i++) extend(i, s[i]);
	}
	void getright()
	{
		for (int i=0; i<=n; i++) c[i]=0;
		for (int i=1; i<=m; i++) c[st[i].len]++;
		for (int i=1; i<=n; i++) c[i]+=c[i-1];
		for (int i=1; i<=m; i++) d[c[st[i].len]--]=i;
		for (int i=m; i>=2; i--)
		{
			int p=st[d[i]].par;
			right.merge(st[p].root, st[d[i]].root, st[p].root);
			st[p].mx=max(st[p].mx, st[d[i]].mx);
		}
	}
	int dp()
	{
		f[1]=0, g[1]=1; int ans=0;
		for (int i=2; i<=m; i++)
		{
			int p=st[d[i]].par;
			if (g[p]==1||right.query(st[g[p]].root, 1, n, st[d[i]].mx-st[d[i]].len+st[g[p]].len, st[d[i]].mx-1))
				f[d[i]]=f[p]+1, g[d[i]]=d[i];
			else f[d[i]]=f[p], g[d[i]]=g[p];
			ans=max(ans, f[d[i]]);
		}
		return ans;
	}
}
char s[MAXN];
int main()
{
//	freopen("CF700E.in", "r", stdin);
//	freopen("CF700E.out", "w", stdout);
	int n;
	scanf("%d%s", &n, s+1);
	SAM::build(s, n);
	SAM::getright();
	printf("%d\n", SAM::dp());
	return 0;
}

