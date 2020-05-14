#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=110000;
int a[MAXN], op[MAXN];
pair<int, int> asn[MAXN];
vector<pair<int, int>> add[MAXN];
vector<pair<double, int>> mul;
int main()
{
//	freopen("CF521D.in", "r", stdin);
//	freopen("CF521D.out", "w", stdout);
	int k, n, m;
	scanf("%d%d%d", &k, &n, &m);
	for (int i=1; i<=k; i++) scanf("%d", &a[i]);
	for (int i=1; i<=n; i++)
	{
		int p, x;
		scanf("%d%d%d", &op[i], &p, &x);
		if (op[i]==1) asn[p]=max(asn[p], make_pair(x-a[p], i));
		else if (op[i]==2) add[p].push_back(make_pair(x, i));
		else mul.push_back(make_pair(x, i));
	}
	for (int i=1; i<=k; i++)
	{
		add[i].push_back(asn[i]);
		sort(add[i].begin(), add[i].end());
		reverse(add[i].begin(), add[i].end());
		long long cur=a[i];
		for (auto x: add[i])
		{
			mul.push_back(make_pair(1.0*(cur+x.first)/cur, x.second));
			cur+=x.first;
		}
	}
	sort(mul.begin(), mul.end());
	reverse(mul.begin(), mul.end());
	vector<pair<int, int>> ans;
	for (int i=0; i<mul.size()&&i<m; i++)
		if (mul[i].first>1)
			ans.push_back(make_pair(op[mul[i].second], mul[i].second));
	sort(ans.begin(), ans.end());
	printf("%d\n", (int)ans.size());
	for (auto x: ans) printf("%d ", x.second);
	putchar('\n');
	return 0;
}
