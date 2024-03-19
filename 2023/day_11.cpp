#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 140;

int row[N], col[N];
char grid[N][N + 1];

std::vector<std::pair<int, int>> stars;

int main() {
    for (int i = 0; i < N; ++i)
        scanf("%s\n", grid[i]);

    std::fill(row, row + N, 1);
    std::fill(col, col + N, 1);
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (grid[i][j] == '#') {
                row[i] = col[j] = 0;
                stars.emplace_back(i, j);
            }
    for (int i = 1; i < N; ++i) {
        row[i] += row[i - 1];
        col[i] += col[i - 1];
    }

    long long part_1 = 0, part_2 = 0;
    for (int i = 0; i < stars.size(); ++i)
        for (int j = i + 1; j < stars.size(); ++j) {
            int x1 = std::min(stars[i].first, stars[j].first);
            int y1 = std::min(stars[i].second, stars[j].second);
            int x2 = std::max(stars[i].first, stars[j].first);
            int y2 = std::max(stars[i].second, stars[j].second);
            long long base_dist = (x2 - x1) + (y2 - y1);
            long long extra_dist = (row[x2] - row[x1]) + (col[y2] - col[y1]);
            part_1 += base_dist + extra_dist;
            part_2 += base_dist + 999999 * extra_dist;
        }
    printf("%lld\n", part_1);
    printf("%lld\n", part_2);
}
