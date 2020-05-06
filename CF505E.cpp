#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
const int MAXN=110000;
int n, m, k, p;
int h[MAXN], a[MAXN];
struct cmp
{
	bool operator () (const pli& lhs, const pli& rhs) const
	{
		return lhs.first/a[lhs.second]>rhs.first/a[rhs.second];
	}
};
bool check(ll r)
{
	priority_queue<pli, vector<pli>, cmp> pq;
	for (int i=1; i<=n; i++)
		if (r-1ll*a[i]*m<h[i]) pq.push(make_pair(r, i));
	for (int i=1; i<=m; i++)
	{
		for (int j=1; j<=k; j++)
		{
			if (pq.empty()) return 1;
			pli t=pq.top(); pq.pop();
			if (t.first-1ll*a[t.second]*i<0) return 0;
			t.first+=p;
			if (t.first-1ll*a[t.second]*m<h[t.second]) pq.push(t);
		}
	}
	return pq.empty();
}
int main()
{
//	freopen("CF505E.in", "r", stdin);
//	freopen("CF505E.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &k, &p);
	for (int i=1; i<=n; i++)
		scanf("%d%d", &h[i], &a[i]);
	ll l=0, r=5.1E12;
	while (l<r)
	{
		ll mid=l+r>>1;
		if (check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%lld\n", l);
	return 0;
}
