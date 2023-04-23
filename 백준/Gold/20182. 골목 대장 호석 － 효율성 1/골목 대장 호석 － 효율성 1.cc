#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321
#define MAX 100001

using namespace std;

int N, M, A, B, C, Dist[MAX];
vector<pair<int, int>> Adj[MAX];

bool Di(int max_cost) {
    priority_queue<pair<int, int>> pq;

    Dist[A] = 0;
    pq.emplace(0, A);

    while (!pq.empty()) {
        int curr_node = pq.top().second;
        int curr_cost = -pq.top().first;
        pq.pop();

        if (curr_node == B)
            return true;

        for (auto &next: Adj[curr_node]) {
            int next_node = next.first;
            int next_cost = curr_cost + next.second;

            if (Dist[next_node] > next_cost) {
                if (next_cost > max_cost)
                    continue;
                if (next_cost > C)
                    continue;

                Dist[next_node] = next_cost;
                pq.emplace(next_cost, next_node);
            }
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> N >> M >> A >> B >> C;

    int n1, n2, dist;
    for (int i = 0; i < M; ++i) {
        cin >> n1 >> n2 >> dist;

        Adj[n1].emplace_back(n2, dist);
        Adj[n2].emplace_back(n1, dist);
    }

    int left = 0, right = 21, mid, ret = INF;
    while (left + 1 < right) {
        fill(Dist, Dist + MAX, INF);
        mid = (left + right) / 2;

        if (Di(mid)) {
            right = mid;
            ret = mid;
        } else {
            left = mid;
        }
    }

    if (ret == INF)
        cout << -1 << '\n';
    else
        cout << ret << '\n';

    return 0;
}