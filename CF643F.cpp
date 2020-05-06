#include <cstdio>
#include <algorithm>
const int MAXP=150;
using namespace std;
unsigned c[MAXP], d[MAXP];
int main()
{
//	freopen("CF643F.in", "r", stdin);
//	freopen("CF643F.out", "w", stdout);
	int n, p, q;
	scanf("%d%d%d", &n, &p, &q);
	p=min(p, n-1);
	for (int i=0; i<=p; i++)
	{
		for (int j=1; j<=i; j++) d[j]=n-j+1;
		for (int j=1; j<=i; j++)
		{
			unsigned t=j;
			for (int k=1; k<=i&&t!=1; k++)
			{
				int g=__gcd(d[k], t);
				d[k]/=g, t/=g;
			}
		}
		c[i]=1;
		for (int j=1; j<=i; j++) c[i]*=d[j];
	}
	unsigned ans=0;
	for (int i=1; i<=q; i++)
	{
		unsigned t=i, s=0;
		for (int j=0; j<=p; j++) s+=c[j]*t, t*=i;
		ans^=s;
	}
	printf("%u\n", ans);
	return 0;
}
