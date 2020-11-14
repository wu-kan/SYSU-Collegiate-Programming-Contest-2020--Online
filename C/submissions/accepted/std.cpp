#include <bits/stdc++.h>
using namespace std;
const pair<int, int> dir[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int maxn = 105;
char a[maxn][maxn];
bool vis[maxn][maxn];
int main()
{
	int _;
	cin >> _;
	while (_--)
	{
		int n;
		cin >> n;
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++)
			cin >> a[i];
		queue<pair<int, int>> q;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if ((i == 0 || j == 0 || i == n - 1 || j == n - 1) && a[i][j] != '#')
				{
					vis[i][j] = true;
					q.emplace(i, j);
				}
			}
		}
		while (q.size())
		{
			auto it = q.front();
			q.pop();
			for (int i = 0; i < 4; i++)
			{
				int r = it.first + dir[i].first;
				int c = it.second + dir[i].second;
				if (r < 0 || r >= n || c < 0 || c >= n)
					continue;
				if (vis[r][c] || a[r][c] == '#')
					continue;
				vis[r][c] = true;
				q.emplace(r, c);
			}
		}
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!vis[i][j] && a[i][j] == 'O')
					ans++;
			}
		}
		cout << ans << "\n";
	}
}