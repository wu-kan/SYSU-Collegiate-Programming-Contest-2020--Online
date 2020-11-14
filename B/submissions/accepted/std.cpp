#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, ans = 0;
	scanf("%d", &n);
	for (int a = 1; a <= n; ++a)
		for (int b = a; b <= n; ++b)
		{
			double cc = sqrt(a * a + b * b);
			int c = cc;
			if (b <= c && c <= n && c == cc)
				++ans;
		}
	printf("%d", ans);
}