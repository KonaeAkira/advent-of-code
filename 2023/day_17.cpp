#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int INF = 1e9;
const int MAX_N = 200;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int n, m, cost[MAX_N][MAX_N][4];
char grid[MAX_N][MAX_N];

struct State {
    int x, y, dir, cost;
};

bool operator < (State const &lhs, State const &rhs) {
    return lhs.cost > rhs.cost;
}

void read_input() {
    while (scanf("%s\n", grid[n]) == 1) ++n;
    m = strlen(grid[0]);
}

int solve(int min_steps, int max_steps) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            std::fill(cost[i][j], cost[i][j] + 4, INF);

    std::priority_queue<State> heap;
    heap.push({0, 0, 0, 0});
    heap.push({0, 0, 1, 0});

    while (!heap.empty()) {
        State cur = heap.top(); heap.pop();
        if (cost[cur.x][cur.y][cur.dir] != INF) continue;
        cost[cur.x][cur.y][cur.dir] = cur.cost;
        for (int i = 1; i <= max_steps; ++i) {
            cur.x += dx[cur.dir]; cur.y += dy[cur.dir];
            if (cur.x < 0 || cur.x >= n || cur.y < 0 || cur.y >= m) break;
            cur.cost += grid[cur.x][cur.y] - '0';
            if (i >= min_steps) {
                heap.push({cur.x, cur.y, (cur.dir + 3) % 4, cur.cost});
                heap.push({cur.x, cur.y, (cur.dir + 1) % 4, cur.cost});
            }
        }
    }

    return std::min(cost[n - 1][m - 1][0], cost[n - 1][m - 1][1]);
}

int main() {
    read_input();
    printf("%d\n", solve(1, 3));
    printf("%d\n", solve(4, 10));
}
