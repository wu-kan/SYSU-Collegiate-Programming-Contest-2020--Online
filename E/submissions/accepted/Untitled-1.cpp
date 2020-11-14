#include <bits/stdc++.h>
#define MAX 1100
#define MAXP 1000100
#define MAXE 2000100
#define INF 0x3f3f3f3f
#define S 0
#define T (MAXP - 1)
using namespace std;

int cooks, chefs;
int need[MAX];
int src[MAX][MAX], cnt;

int now[MAX];

struct MinCostMaxFlow
{
	int head[MAXP], total;
	int _next[MAXE], aim[MAXE], flow[MAXE], cost[MAXE];
	int f[MAXP], from[MAXP], p[MAXP];
	bool v[MAXP];
	void Add(int x, int y, int f, int c)
	{
		_next[++total] = head[x];
		aim[total] = y;
		flow[total] = f;
		cost[total] = c;
		head[x] = total;
	}
	void Insert(int x, int y, int f, int c)
	{
		Add(x, y, f, c);
		Add(y, x, 0, -c);
	}
	void Initialize()
	{
		for (int i = 1; i <= chefs; ++i)
		{
			Insert(i, ++cnt, 1, 0);
			for (int j = 1; j <= cooks; ++j)
				Insert(cnt, chefs + j, 1, src[j][i]);
		}
	}
	bool SPFA()
	{
		static queue<int> q;
		while (!q.empty())
			q.pop();
		memset(f, 0x3f, sizeof(f));
		f[S] = 0;
		q.push(S);
		while (!q.empty())
		{
			int x = q.front();
			q.pop();
			v[x] = false;
			for (int i = head[x]; i; i = _next[i])
				if (flow[i] && f[aim[i]] > f[x] + cost[i])
				{
					f[aim[i]] = f[x] + cost[i];
					if (!v[aim[i]])
					{
						v[aim[i]] = true;
						q.push(aim[i]);
					}
					from[aim[i]] = x;
					p[aim[i]] = i;
				}
		}
		return f[T] != INF;
	}
	int EdmondsKarp()
	{
		int re = 0;
		while (SPFA())
		{
			int remain_flow = INF;
			for (int i = T; i != S; i = from[i])
				remain_flow = min(remain_flow, flow[p[i]]);
			static int k, temp;
			for (int i = T; i != S; i = from[i])
			{
				flow[p[i]] -= remain_flow;
				flow[p[i] ^ 1] += remain_flow;
				if (i <= chefs && i >= 1)
					k = i;
				if (i != T && i > chefs)
					temp = i;
			}
			++now[k];
			Insert(k, ++cnt, 1, 0);
			for (int i = 1; i <= cooks; ++i)
				Insert(cnt, chefs + i, 1, (now[k] + 1) * src[i][k]);
			re += f[T] * remain_flow;
		}
		return re;
	}
	void clear()
	{
		for (int i = 0; i < MAX; i++)
		{
			now[i] = 0;
		}
		for (int i = 0; i <= total; i++)
		{
			aim[i] = 0;
			_next[i] = 0;
			flow[i] = 0;
			cost[i] = 0;
		}
		for (int i = 0; i <= T; i++)
			head[i] = 0, v[i] = 0;
		total = 1, cnt = 0;
	}
} solver;
int main()
{
	//	freopen("ProblemA.in", "r", stdin);
	int TT;
	scanf("%d", &TT);
	while (TT--)
	{
		solver.clear();
		scanf("%d%d", &chefs, &cooks);
		for (int i = 1; i <= cooks; ++i)
			need[i] = 1;
		for (int i = 1; i <= cooks; ++i)
			for (int j = 1; j <= chefs; ++j)
				scanf("%d", &src[i][j]);
		for (int i = 1; i <= chefs; ++i)
			solver.Insert(S, ++cnt, INF, 0);
		int p = 0;
		for (int i = 1; i <= cooks; ++i)
		{
			solver.Insert(++cnt, T, need[i], 0);
			p += need[i];
		}
		solver.Initialize();
		printf("%d\n", solver.EdmondsKarp());
	}
	return 0;
}
