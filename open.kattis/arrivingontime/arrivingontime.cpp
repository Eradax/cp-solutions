#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

typedef vector<ll> vll;
typedef vector<vll> vvll;

typedef pair<ll, ll> p2;
typedef vector<p2> vp2;
typedef vector<vp2> vvp2;

ll stops, lines, meeting;

vvp2 graph;
vvp2 times;

vll dist;

priority_queue<p2, vp2, greater<p2>> pq;

ll waitTime(ll time, ll start, ll end) {
    if (time <= times[start][end].first) {
        return times[start][end].first - time;
    } else {
        ll firstTrain = time - times[start][end].first;
        ll lastTrain = firstTrain % times[start][end].second;

        return (lastTrain == 0) ? 0 : (times[start][end].second - lastTrain);
    }
}

ll dijkstra(ll startTime) {
	dist.clear();
	dist.resize(stops, 1e18);
    dist[0] = startTime;
    pq.push({startTime, 0});
    while (!pq.empty()) {
		ll len, v;
        tie(len,v) = pq.top(); pq.pop();

        if (len == dist[v]) {
            for (auto node: graph[v]) {
                if (node.second + len + waitTime(len, v, node.first) < dist[node.first]) {
                    dist[node.first] = node.second + len + waitTime(len, v, node.first);
                    pq.push({dist[node.first], node.first});
                }
            }
        }
    }
    return dist.back();
}

int main() {
    cin >> stops >> lines >> meeting;
    graph.resize(stops, vp2());
    times.resize(stops, vp2(stops));

    for (int i=0; i<lines; i++) {
        ll start, end, first, cycle, length;
        cin >> start >> end >> first >> cycle >> length;

        graph[start].push_back({end, length});
        times[start][end] = {first, cycle};
    }

	dist.resize(stops, 1e18);
    ll lo=0, hi=meeting;
    while (lo < hi) {
        ll mi = (lo+hi+1)/2;
        if (dijkstra(mi) > meeting) {
            hi = mi-1;
        } else {
            lo = mi;
        }
    }

    if (dijkstra(lo) <= meeting) {
        cout << lo << endl;
    } else {
        cout << "impossible" << endl;
    }
}