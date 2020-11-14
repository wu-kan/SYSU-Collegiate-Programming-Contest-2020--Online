#include <bits/stdc++.h>
using namespace std;

const int maxn = 10000;
int n;
int L[maxn], R[maxn];

bool test(double delta)
{
	bool used[maxn];
	memset(used, 0, sizeof(used));
	double A = 0;
	while (A < 9999.9999)
	{
		int x, maxr = 10001;
		for (int i = 0; i < n; i++)
			if ((!used[i]) && (R[i] < maxr) && (A >= L[i] - delta) && (A <= R[i] + delta))
			{
				x = i;
				maxr = R[i];
			}
		if (maxr == 10001)
			return false;
		used[x] = true;
		if (A <= delta + L[x])
			A = A + R[x] - L[x];
		else
			A = R[x] + delta;
	}
	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d%d", &L[i], &R[i]);

	double l = 0;
	double r = 10000;
	while (r - l > 0.001)
	{
		double now = (l + r) / 2;
		if (test(now))
			r = now;
		else
			l = now;
	}

	int ans = round(r + l);
	printf("%d", ans >> 1);
	if (ans & 1)
		printf(".5");
}
