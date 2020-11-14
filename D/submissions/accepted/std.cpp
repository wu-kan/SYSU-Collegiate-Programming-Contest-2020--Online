#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 9, M = 1e4;
const double EPS = 0.25;
pair<int, int> p[N];
int n;
int ok(double delta)
{
	priority_queue<pair<int, int>> q;
	int i = 0;
	for (double A = 0; A < M - EPS;)
	{
		for (; i < n && p[i].first <= A + delta + EPS; ++i)
			q.push({-p[i].second, i});
		int updated = 0;
		for (int x, l, r; !q.empty() && !updated; q.pop())
			if (x = q.top().second, l = p[x].first, r = p[x].second,
				A <= r + delta + EPS)
			{
				if (A > l + delta)
					A = r + delta;
				else
					A += r - l;
				updated = 1;
			}
		if (!updated)
			return 0;
	}
	return 1;
}
int bs(int b, int e)
{
	if (e - b < 2)
		return e;
	int m = b + (e - b >> 1);
	return ok(m * 0.5) ? bs(b, m) : bs(m, e);
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &p[i].first, &p[i].second);
	sort(p, p + n);
	int ans = bs(0, M << 1);
	printf("%d", ans >> 1);
	if (ans & 1)
		printf(".5");
}