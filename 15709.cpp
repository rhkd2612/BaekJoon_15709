#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
#define MAX 20101

struct edge
{
	int to;
	ll weight;
public:
	edge(int t, ll w)
	{
		to = t;
		weight = w;
	}
};

bool operator>(const edge & e1, const edge & e2)
{
	return e1.weight > e2.weight;
}

vector<edge> canGo[MAX];

ll graph[101][MAX];

int main()
{
	int house, hosp, brid, road, _case;

	cin >> house >> hosp >> brid >> road >> _case;

	int s = house + hosp + brid;
	int bridFirst = house + hosp + 1;

	for (int j = 1; j <= brid; j++)
	{
		for (int i = 1; i <= s; i++)
		{
			graph[j][i] = LLONG_MAX;
		}
	}

	for (int i = 0; i < road; i++)
	{
		int from, to, w;

		scanf("%d %d %d", &from, &to, &w);

		canGo[from].push_back(edge(to, w));
		canGo[to].push_back(edge(from, w));
	}

	for (int j = bridFirst; j <= s; j++)
	{
		if (canGo[j].size() == 0)
			continue;

		int idx = j - bridFirst+1;
		graph[idx][j] = 0;

		priority_queue < edge, vector<edge>, greater<edge>> q;
		q.push(edge(j, 0));

		while (!q.empty())
		{
			edge temp = q.top(); q.pop();

			if (temp.weight > graph[idx][temp.to])
				continue;

			for (auto a : canGo[temp.to])
			{
				int dir = a.to;
				ll w = a.weight + temp.weight;

				if (w < graph[idx][dir])
				{
					graph[idx][dir] = w;
					q.push(edge(dir, w));
				}
			}
		}
	}

	for (int i = 0; i < _case; i++)
	{
		int from, to;

		scanf("%d %d", &from, &to);

		ll m = LLONG_MAX;

		for (int j = 1; j <= brid; j++)
		{
			if(graph[j][from] != LLONG_MAX && graph[j][to] != LLONG_MAX)
				m = min(m, graph[j][from] + graph[j][to]);
		}

		if (m == LLONG_MAX)
			m = -1;

		printf("%lld\n", m);
	}

	return 0;
}


