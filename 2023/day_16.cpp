#include <cstdio>
#include <cstring>
#include <bitset>

const int MAX_N = 200;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int n, m;
char grid[MAX_N][MAX_N];
std::bitset<4> vis[MAX_N][MAX_N];

void read_input() {
    while (scanf("%s\n", grid[n]) == 1) ++n;
    m = strlen(grid[0]);
}

bool straight(char c, int d) {
    return c == '.' || (c == '|' && d % 2 == 1) || (c == '-' && d % 2 == 0);
}

bool left(char c, int d) {
    return (c == '|' && d % 2 == 0) || (c == '-' && d % 2 == 1)
        || (c == '\\' && d % 2 == 1) || (c == '/' && d % 2 == 0);
}

bool right(char c, int d) {
    return (c == '|' && d % 2 == 0) || (c == '-' && d % 2 == 1)
        || (c == '\\' && d % 2 == 0) || (c == '/' && d % 2 == 1);
}

void dfs(int x, int y, int d) {
    if (x < 0 || x >= n || y < 0 || y >= m || vis[x][y].test(d)) return;
    vis[x][y].set(d);
    if (straight(grid[x][y], d)) dfs(x + dx[d], y + dy[d], d);
    if (left(grid[x][y], d)) dfs(x + dx[(d + 3) % 4], y + dy[(d + 3) % 4], (d + 3) % 4);
    if (right(grid[x][y], d)) dfs(x + dx[(d + 1) % 4], y + dy[(d + 1) % 4], (d + 1) % 4);
}

int count_and_reset(int x, int y, int d) {
    dfs(x, y, d);
    int count = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            count += vis[i][j].any();
            vis[i][j].reset();
        }
    return count;
}

int main() {
    read_input();

    printf("%d\n", count_and_reset(0, 0, 0));

    int part_2 = 0;
    for (int i = 0; i < n; ++i) {
        part_2 = std::max(part_2, count_and_reset(i, 0, 0));
        part_2 = std::max(part_2, count_and_reset(i, m - 1, 2));
    }
    for (int j = 0; j < m; ++j) {
        part_2 = std::max(part_2, count_and_reset(0, j, 1));
        part_2 = std::max(part_2, count_and_reset(n - 1, j, 3));
    }
    printf("%d\n", part_2);
}
