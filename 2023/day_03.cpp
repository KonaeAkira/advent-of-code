#include <cstdio>
#include <string>
#include <vector>

const int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int n, m;
std::vector<std::string> grid;

void read_input() {
    char buf[1024];
    while (scanf("%s\n", buf) == 1) grid.push_back(buf);
    n = grid.size(); m = grid.back().size();
}

bool is_digit(char c) { return c >= '0' && c <= '9'; }

int get_number(int x, int y) {
    while (y > 0 && is_digit(grid[x][y - 1])) --y;
    int num = 0;
    while (y < m && is_digit(grid[x][y])) num = num * 10 + grid[x][y++] - '0';
    return num;
}

bool has_symbol(int x, int y) {
    for (int i = 0; i < 8; ++i) {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 0 && a < n && b >= 0 && b < m) {
            char c = grid[a][b];
            if (c != '.' && !(c >= '0' && c <= '9')) return true;
        }
    }
    return false;
}

int main() {
    read_input();

    long long part_1 = 0, part_2 = 0;

    for (int i = 0; i < n; ++i) {
        int acc = 0, acc2 = 0; bool sym = false;
        for (int j = 0; j < m; ++j)
            if (grid[i][j] >= '0' && grid[i][j] <= '9') {
                acc = acc * 10 + grid[i][j] - '0';
                sym |= has_symbol(i, j);
            } else if (grid[i][j] == '*') {
                part_1 += acc;
                acc2 = acc; acc = 0;
            } else {
                if (sym) part_1 += acc;
                part_2 += acc * acc2;
                acc = acc2 = 0; sym = false;
            }
        if (sym) part_1 += acc;
        part_2 += acc * acc2;
    }

    printf("%lld\n%lld\n", part_1, part_2);
}