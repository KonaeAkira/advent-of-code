#include <iostream>
#include <vector>

const int INF = 1e9;

const int MAX_X = 150;
const int MAX_Y = 150;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

typedef std::pair<int, int> Point;

std::vector<std::string> grid;
std::vector<Point> slopes;

bool visited[MAX_X][MAX_Y];

void read_input() {
    std::string line;
    while (std::cin >> line) {
        grid.push_back(line);
    }
    grid.front()[1] = 'v';
    grid.back()[grid.back().size() - 2] = 'v';
}

bool in_grid(Point p) {
    return p.first >= 0 && p.first < grid.size() && p.second >= 0 && p.second < grid[0].size();
}

int solve(Point cur) {
    visited[cur.first][cur.second] = true;
    int result = (cur == slopes.back() ? 0 : -INF);
    for (int i = 0; i < 4; ++i) {
        Point nxt{cur.first + dx[i], cur.second + dy[i]};
        if (!in_grid(nxt) || grid[nxt.first][nxt.second] == '#') continue;
        if (grid[nxt.first][nxt.second] == '>' && i != 0) continue;
        if (grid[nxt.first][nxt.second] == 'v' && i != 1) continue;
        if (!visited[nxt.first][nxt.second]) result = std::max(result, solve(nxt) + 1);
    }
    visited[cur.first][cur.second] = false;
    return result;
}

int main() {
    read_input();

    for (int i = 0; i < grid.size(); ++i)
        for (int j = 0; j < grid[i].size(); ++j)
            if (grid[i][j] == '>' || grid[i][j] == 'v') {
                slopes.emplace_back(i, j);
            }

    printf("%d\n", solve(slopes.front()));

    for (Point p : slopes) grid[p.first][p.second] = '.';
    printf("%d\n", solve(slopes.front()));
}
