#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=110;
const int INF=1E9;
struct Node
{
	int p, l;
	bool operator < (const Node& rhs) const
	{
		return p<rhs.p;
	}
} a[MAXN];
int f[MAXN][MAXN][2];
int main()
{
//	freopen("CF559E.in", "r", stdin);
//	freopen("CF559E.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i=1; i<=n; i++)
		scanf("%d%d", &a[i].p, &a[i].l);
	sort(a+1, a+n+1), a[0].p=-INF;
	int ans=0;
	for (int i=0; i<=n; i++)
		for (int j=0; j<=i; j++)
			for (int p=0; p<2; p++)
			{
				ans=max(ans, f[i][j][p]);
				int o=a[j].p+p*a[j].l, mx=-INF, x, y;
				for (int k=i+1; k<=n; k++)
					for (int q=0; q<2; q++)
					{
						int t=a[k].p+q*a[k].l;
						if (t>mx) mx=t, x=k, y=q;
						f[k][x][y]=max(f[k][x][y], f[i][j][p]+min(a[k].l, t-o)+mx-t);
					}
			}
	printf("%d\n", ans);
	return 0;
}
