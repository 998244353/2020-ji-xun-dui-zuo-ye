#include <cstdio>
#include <cmath>
#include <set>
using namespace std;
typedef long double ld;
const int MAXN=220000;
const ld INF=1E18, EPS=1E-10;
int p[MAXN], l[MAXN], c[MAXN];
struct Node
{
	int x; ld v;
	Node(int a, int b): x(a)
	{
		if (b==-1) v=INF;
		else if (b>=l[a]) v=0;
		else v=1.0L*p[a]*l[a]/(b+1+l[a])/(b+l[a]);
	}
	bool operator < (const Node& rhs) const
	{
		return abs(v-rhs.v)>EPS?v<rhs.v:x<rhs.x;
	}
};
set<Node> A, B;
ld ans=0;
ld calc(int x)
{
	int t=min(c[x], l[x]);
	return 1.0L*p[x]*t/(t+l[x]);
}
void add()
{
	auto it=--A.end();
	ans+=it->v; int x=it->x;
	B.erase(Node(x, c[x]-1)), B.insert(*it);
	A.erase(it), A.insert(Node(x, ++c[x]));
}
void del()
{
	auto it=B.begin();
	ans-=it->v; int x=it->x;
	A.erase(Node(x, c[x])), A.insert(*it);
	B.erase(it), B.insert(Node(x, --c[x]-1));
}
int main()
{
//	freopen("CF626G.in", "r", stdin);
//	freopen("CF626G.out", "w", stdout);
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	for (int i=1; i<=n; i++) scanf("%d", &p[i]);
	for (int i=1; i<=n; i++)
	{
		scanf("%d", &l[i]);
		A.insert(Node(i, 0));
		B.insert(Node(i, -1));
	}
	while (m--) add();
	while (q--)
	{
		int k, x;
		scanf("%d%d", &k, &x);
		A.erase(Node(x, c[x]));
		B.erase(Node(x, c[x]-1));
		ans-=calc(x);
		l[x]+=k==1?1:-1;
		A.insert(Node(x, c[x]));
		B.insert(Node(x, c[x]-1));
		ans+=calc(x);
		del(), add();
		printf("%.10lf\n", (double)ans);
	}
	return 0;
}
