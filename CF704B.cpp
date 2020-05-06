#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN=5500;
const ll INF=1E18;
int x[MAXN], a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int nxt[MAXN];
inline ll calc(int i, int j)
{
	return i>j?(ll)x[i]-x[j]+c[i]+b[j]:(ll)x[j]-x[i]+d[i]+a[j];
}
int main()
{
//	freopen("B.in", "r", stdin);
//	freopen("B.out", "w", stdout);
	int n, s, e;
	scanf("%d%d%d", &n, &s, &e);
	for (int i=1; i<=n; i++) scanf("%d", &x[i]);
	for (int i=1; i<=n; i++) scanf("%d", &a[i]);
	for (int i=1; i<=n; i++) scanf("%d", &b[i]);
	for (int i=1; i<=n; i++) scanf("%d", &c[i]);
	for (int i=1; i<=n; i++) scanf("%d", &d[i]);
	nxt[s]=e;
	for (int i=1; i<=n; i++)
		if (i!=s&&i!=e)
		{
			ll mn=INF; int pos;
			for (int j=s; j!=e; j=nxt[j])
			{
				ll t=calc(j, i)+calc(i, nxt[j])-calc(j, nxt[j]);
				if (t<mn) mn=t, pos=j;
			}
			nxt[i]=nxt[pos], nxt[pos]=i;
		}
	ll ans=0;
	for (int i=s; i!=e; i=nxt[i]) ans+=calc(i, nxt[i]);
	printf("%lld\n", ans);
	return 0;
}
