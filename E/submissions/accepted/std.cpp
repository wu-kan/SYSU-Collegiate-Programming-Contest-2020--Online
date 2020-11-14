#include <bits/stdc++.h>
using namespace std;
typedef int ll;
const ll INF = 1e9, M = 255, N = 63;
int t, n, m, tim[M][N];
struct Graph
{
	struct Vertex
	{
		vector<int> o;
	};
	struct Edge
	{
		int first, second;
		ll len, cap;
	};
	vector<Vertex> v;
	vector<Edge> e;
	Graph(int n) : v(n) {}
	void add(const Edge &ed)
	{
		v[ed.first].o.push_back(e.size());
		e.push_back(ed);
	}
};
struct PrimalDual : Graph
{
	ll flow, cost;
	vector<ll> f;
	PrimalDual(int n) : Graph(n) {}
	void add(Edge ed)
	{
		Graph::add(ed);
		swap(ed.first, ed.second), ed.cap = 0, ed.len *= -1;
		Graph::add(ed);
	}
	void ask(int s, int t)
	{
		vector<int> p(v.size(), -1), now(n, 1);
		vector<ll> d(v.size(), INF), h(v.size(), 0);
		for (f.assign(e.size(), flow = cost = 0);;)
		{
			priority_queue<pair<ll, int>> q;
			for (q.push(make_pair(d[s] = 0, s)); !q.empty();)
			{
				ll dis = -q.top().first;
				int u = q.top().second;
				if (q.pop(), d[u] < dis)
					continue;
				for (int i = 0, k, to; i < v[u].o.size(); ++i)
					if (k = v[u].o[i], to = e[k].second,
						e[k].cap > f[k] && d[to] > d[u] + e[k].len + h[u] - h[to])
					{
						d[to] = d[u] + e[k].len + h[u] - h[to], p[to] = k;
						q.push(make_pair(-d[to], to));
					}
			}
			if (d[t] == INF)
				return;
			for (int i = 0; i < d.size(); ++i)
				if (d[i] != INF)
					h[i] += d[i], d[i] = INF;
			ll _f = INF;
			for (int u = t; u != s; u = e[p[u]].first)
				_f = min(_f, e[p[u]].cap - f[p[u]]);
			for (int u = t; u != s; u = e[p[u]].first)
				cost += _f * e[p[u]].len, f[p[u]] += _f, f[p[u] ^ 1] -= _f;
			flow += _f;
			for (int u = t; u != s; u = e[p[u]].first)
				if (1 < u && u < n + 2)
				{
					int k = u - 2;
					++now[k];
					p.push_back(-1);
					d.push_back(INF);
					h.push_back(0);
					v.push_back(Vertex());
					add({u, v.size() - 1, 0, 1});
					for (int i = 0; i < m; ++i)
						add({v.size() - 1, 2 + n + i, now[k] * tim[i][k], 1});
					f.resize(e.size(), 0);
					break;
				}
		}
	}
};
int main()
{
	for (scanf("%d", &t); t--;)
	{
		scanf("%d%d", &n, &m);
		PrimalDual g(2 + n + m + n);
		for (int j = 0; j < n; ++j)
		{
			g.add({0, 2 + j, 0, INF});
			g.add({2 + j, 2 + n + m + j, 0, 1});
		}
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				scanf("%d", &tim[i][j]);
				g.add({2 + n + m + j, 2 + n + i, tim[i][j], 1});
			}
			g.add({2 + n + i, 1, 0, 1});
		}
		g.ask(0, 1);
		printf("%d\n", g.cost);
	}
}