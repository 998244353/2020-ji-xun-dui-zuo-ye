#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int, int> pii;
const int MAXN=110000;
const int INF=1E9+233;
int a[MAXN], b[MAXN];
pii f[MAXN], g[MAXN];
multiset<int> s;
int main()
{
//	freopen("CF568E.in", "r", stdin);
//	freopen("CF568E.out", "w", stdout);
	int n, m;
	scanf("%d", &n);
	for (int i=1; i<=n; i++) scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i=1; i<=m; i++)
		scanf("%d", &b[i]), s.insert(b[i]);
	sort(b+1, b+m+1);
	for (int i=1; i<=n; i++) g[i]=make_pair(INF, 0);
	for (int i=1; i<=n; i++)
		if (~a[i])
		{
			int p=lower_bound(g, g+n+1, pii(a[i], 0))-g-1;
			f[i]=pii(p+1, g[p].second);
			g[p+1]=min(g[p+1], pii(a[i], i));
		}
		else
			for (int j=m, k=n; j>=1; j--)
			{
				while (g[k].first>=b[j]) k--;
				g[k+1]=min(g[k+1], pii(b[j], i));
			}
	for (int i=n; i>=0; i--)
		if (g[i].first!=INF)
		{
			int p=g[i].second, v=g[i].first, l=i;
			while (p)
			{
				if (~a[p])
				{
					p=f[p].second;
					if (~a[p]) v=a[p];
					else v=*(lower_bound(b+1, b+m+1, v)-1);
				}
				else
				{
					a[p]=v, s.erase(s.find(v));
					int q; bool flag=0;
					for (int j=0; j<p; j++)
						if (a[j]==-1) q=j;
						else if (a[j]<v&&f[j].first==l-1)
							{ p=j, v=a[j], flag=1; break; }
					if (!flag) p=q, v=*(lower_bound(b+1, b+m+1, v)-1);
				}
				l--;
			}
			break;
		}
	for (int i=1; i<=n; i++)
	{
		if (a[i]==-1)
			a[i]=*s.begin(), s.erase(s.begin());
		printf("%d ", a[i]);
	}
	putchar('\n');
	return 0;
}
