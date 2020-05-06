#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN=550000;
const int MAXM=2*MAXN;
struct Pair
{
	int mx, pos;
	Pair(int a=0, int b=1): mx(a), pos(b) {}
	bool operator < (const Pair& rhs) const
	{
		return mx<rhs.mx||mx==rhs.mx&&pos>rhs.pos;
	}
};
int n, m, q;
namespace SAM
{
	struct SegmentTree
	{
		struct Node
		{
			int ls, rs; Pair val;
		} tr[MAXN<<5];
		int cnt;
		int newNode(int p=0)
		{
			int x=++cnt;
			tr[x].ls=tr[x].rs=0;
			tr[x].val=Pair(0, p);
			return x;
		}
		void pushup(int x)
		{
			tr[x].val=max(tr[tr[x].ls].val, tr[tr[x].rs].val);
		}
		void add(int& x, int l, int r, int p)
		{
			if (!x) x=newNode(l);
			if (l==r) { tr[x].val.mx++; return; }
			int mid=l+r>>1;
			if (p<=mid) add(tr[x].ls, l, mid, p);
			else add(tr[x].rs, mid+1, r, p);
			pushup(x);
		}
		void merge(int x, int y, int& z, int l, int r)
		{
			z=newNode();
			if (!x||!y) { tr[z]=x?tr[x]:tr[y]; return; }
			if (l==r) { tr[z].val=Pair(tr[x].val.mx+tr[y].val.mx, l); return; }
			int mid=l+r>>1;
			merge(tr[x].ls, tr[y].ls, tr[z].ls, l, mid);
			merge(tr[x].rs, tr[y].rs, tr[z].rs, mid+1, r);
			pushup(z);
		}
		Pair query(int x, int l, int r, int ql, int qr)
		{
			if (!x||l>qr||r<ql) return Pair();
			if (ql<=l&&r<=qr) return tr[x].val;
			int mid=l+r>>1;
			return max(query(tr[x].ls, l, mid, ql, qr),
			           query(tr[x].rs, mid+1, r, ql, qr));
		}
	} sgt;
	int ch[MAXM][26], fa[MAXM][20];
	int len[MAXM], rt[MAXM];
	int end[MAXM], mx[MAXM];
	vector<int> g[MAXM];
	int m, root, lst;
	int newNode(int l)
	{
		m++;
		memset(ch[m], 0, sizeof ch[m]);
		len[m]=l, fa[m][0]=rt[m]=0;
		return m;
	}
	void extend(char c)
	{
		int x=c-'a', p=lst, np=ch[p][x];
		if (np&&len[np]==len[p]+1) { lst=np; return; }
		np=newNode(len[p]+1);
		while (p&&!ch[p][x]) ch[p][x]=np, p=fa[p][0];
		if (!p) fa[np][0]=root;
		else
		{
			int q=ch[p][x];
			if (len[q]==len[p]+1) fa[np][0]=q;
			else
			{
				int nq=newNode(len[p]+1);
				memcpy(ch[nq], ch[q], sizeof ch[q]);
				fa[nq][0]=fa[q][0], fa[q][0]=fa[np][0]=nq;
				if (p==lst) np=nq;
				while (p&&ch[p][x]==q) ch[p][x]=nq, p=fa[p][0];
			}
		}
		lst=np;
	}
	void init() { m=sgt.cnt=0, lst=root=newNode(0); }
	void insert(char* s, int d)
	{
		lst=root;
		for (int i=0; s[i]; i++)
			extend(s[i]), sgt.add(rt[lst], 1, ::m, d);
	}
	void dfs(int p)
	{
		for (int i=1; i<20; i++)
			fa[p][i]=fa[fa[p][i-1]][i-1];
		for (int q:g[p])
			dfs(q), sgt.merge(rt[p], rt[q], rt[p], 1, ::m);
	}
	void build(char* s)
	{
		for (int i=2; i<=m; i++)
			g[fa[i][0]].push_back(i);
		dfs(root);
		for (int i=1, p=root, l=0; i<=::n; i++)
		{
			int x=s[i]-'a';
			while (p&&!ch[p][x]) p=fa[p][0], l=len[p];
			if (!p) p=root, l=0;
			else p=ch[p][x], l++;
			end[i]=p, mx[i]=l;
		}
	}
	Pair query(int L, int R, int l, int r)
	{
		if (mx[r]<r-l+1) return Pair(0, 1);
		int p=end[r];
		for (int i=19; i>=0; i--)
			if (len[fa[p][i]]>=r-l+1) p=fa[p][i];
		return sgt.query(rt[p], 1, ::m, L, R);
	}
}
char s[MAXN], t[MAXN];
int main()
{
//	freopen("CF666E.in", "r", stdin);
//	freopen("CF666E.out", "w", stdout);
	scanf("%s%d", s+1, &m);
	n=strlen(s+1);
	SAM::init();
	for (int i=1; i<=m; i++)
	{
		scanf("%s", t);
		SAM::insert(t, i);
	}
	SAM::build(s);
	scanf("%d", &q);
	while (q--)
	{
		int L, R, l, r;
		scanf("%d%d%d%d", &L, &R, &l, &r);
		Pair ret=SAM::query(L, R, l, r);
		printf("%d %d\n", max(ret.pos, L), ret.mx);
	}
	return 0;
}
