#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN=110;
const int MAXT=33000;
const int INF=1E9;
const double PI=acos(-1);
int read()
{
	int x=0; char ch=0;
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x;
}
struct Complex
{
	double x, y;
	Complex(double a=0, double b=0): x(a), y(b) {}
};
Complex operator + (const Complex& a, const Complex& b)
{
	return Complex(a.x+b.x, a.y+b.y);
}
Complex operator - (const Complex& a, const Complex& b)
{
	return Complex(a.x-b.x, a.y-b.y);
}
Complex operator * (const Complex& a, const Complex& b)
{
	return Complex(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
}
int l, r[MAXT];
void getl(int n)
{
	int d=0; l=1; r[0]=0;
	while (l<=n) l<<=1, d++;
	for (int i=1; i<l; i++)
		r[i]=r[i>>1]>>1|(i&1)<<d-1;
}
void fft(Complex* a, int ty)
{
	for (int i=0; i<l; i++)
		if (i<r[i]) swap(a[i], a[r[i]]);
	for (int k=1; k<l; k<<=1)
	{
		Complex wn(cos(PI/k), ty*sin(PI/k));
		for (int i=0; i<l; i+=k<<1)
		{
			Complex w(1, 0);
			for (int j=0; j<k; j++, w=w*wn)
			{
				Complex x=a[i+j], y=w*a[i+k+j];
				a[i+j]=x+y, a[i+k+j]=x-y;
			}
		}
	}
}
struct Edge
{
	int u, v, w;
} e[MAXN];
int n, m, t, x;
int d[MAXN][MAXN];
double p[MAXN][MAXT];
double f[MAXN][MAXT], g[MAXN][MAXT];
void solve(int L, int R)
{
	static Complex a[MAXT], b[MAXT];
	if (L==R)
	{
		for (int i=1; i<=m; i++)
			f[e[i].u][L]=min(f[e[i].u][L], g[i][L]+e[i].w);
		return;
	}
	int mid=L+R>>1;
	solve(mid+1, R);
	getl(R-L+1+R-mid);
	for (int i=1; i<=m; i++)
	{
		for (int j=0; j<l; j++) a[j]=b[j]=0;
		for (int j=0; j<R-L+1; j++) a[j]=p[i][R-L+1-j];
		for (int j=0; j<R-mid; j++) b[j]=f[e[i].v][mid+1+j];
		fft(a, 1); fft(b, 1);
		for (int i=0; i<l; i++) a[i]=a[i]*b[i];
		fft(a, -1);
		for (int j=L; j<=mid; j++)
			g[i][j]+=a[R-mid+j-L].x/l;
	}
	solve(L, mid);
}
int main()
{
//	freopen("CF553E.in", "r", stdin);
//	freopen("CF553E.out", "w", stdout);
	n=read(), m=read(), t=read(), x=read();
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			d[i][j]=i==j?0:INF;
	for (int i=1; i<=m; i++)
	{
		e[i].u=read(), e[i].v=read(), e[i].w=read();
		d[e[i].u][e[i].v]=e[i].w;
		for (int j=1; j<=t; j++) p[i][j]=read()/1E5;
	}
	for (int k=1; k<=n; k++)
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++)
				d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
	for (int i=1; i<n; i++)
		for (int j=0; j<=t; j++) f[i][j]=INF;
	for (int i=1; i<=m; i++)
	{
		double s=0;
		for (int j=0; j<=t; j++)
			g[i][j]=s*(d[e[i].v][n]+x), s+=p[i][t-j];
	}
	solve(0, t);
	printf("%.10lf\n", f[1][0]);
	return 0;
}
