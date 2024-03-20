#include <cstdio>
#include <cmath>
#include <map>
#include <vector>

const int N = 140;

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

const std::map<char, int> mask = {
    {'|', 0b1010},
    {'-', 0b0101},
    {'L', 0b1100},
    {'J', 0b1001},
    {'7', 0b0011},
    {'F', 0b0110},
    {'.', 0b0000},
    {'S', 0b0000}
};

char grid[N][N + 1];
std::pair<int, int> pos_s;
std::map<std::pair<int, int>, std::pair<int, int>> dsu;
std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> adj;

int part_1, part_2;

std::pair<int, int> root(std::pair<int, int> a) {
    if (dsu[a].first < 0) return a;
    else return dsu[a] = root(dsu[a]);
}

void join(std::pair<int, int> a, std::pair<int, int> b) {
    adj[a].push_back(b); adj[b].push_back(a);
    if ((a = root(a)) == (b = root(b))) return;
    dsu[a].first += dsu[b].first; dsu[b] = a;
}

int signed_area(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c) {
    return (a.first - b.first) * (a.second + b.second)
         + (b.first - c.first) * (b.second + c.second)
         + (c.first - a.first) * (c.second + a.second);
}

void solve(std::pair<int, int> a) {
    std::vector<std::pair<int, int>> cycle;
    cycle.push_back(pos_s); cycle.push_back(a);
repeat:
    for (std::pair<int, int> b : adj[cycle.back()])
        if (b != cycle[cycle.size() - 2]) {
            cycle.push_back(b);
            goto repeat;
        }
    int cycle_len = cycle.size() + 1, area = 0;
    for (int i = 1; i + 1 < cycle.size(); ++i)
        area += signed_area(cycle[0], cycle[i], cycle[i + 1]);
    printf("%d\n", cycle_len / 2);  // part_1
    printf("%d\n", std::abs(area) / 2 - cycle_len / 2 + 1);  // part_2
}

int main() {
    for (int i = 0; i < N; ++i) {
        scanf("%s\n", grid[i]);
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 'S') pos_s = {i, j};
            dsu[{i, j}] = {-1, 0};
        }
    }
    
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            if (i + 1 < N && (mask.at(grid[i][j]) & 0b0010) && (mask.at(grid[i + 1][j]) & 0b1000))
                join({i, j}, {i + 1, j});
            if (j + 1 < N && (mask.at(grid[i][j]) & 0b0100) && (mask.at(grid[i][j + 1]) & 0b0001))
                join({i, j}, {i, j + 1});
        }

    for (int i = 0; i < 4; ++i)
        for (int j = i + 1; j < 4; ++j) {
            std::pair<int, int> a = {pos_s.first + dx[i], pos_s.second + dy[i]};
            std::pair<int, int> b = {pos_s.first + dx[j], pos_s.second + dy[j]};
            if (root(a) == root(b)) { solve(a); return 0; }
        }
}
