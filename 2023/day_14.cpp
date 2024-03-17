#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

const int N = 100;
const int STEPS = 1000000000;

char grid[N][N], tmp[N][N];
std::map<long long, int> ind;
std::vector<int> loads;

void read_input() {
    char buf[N + 1];
    for (int i = 0; i < N; ++i) {
        scanf("%s\n", buf);
        memcpy(grid[i], buf, N);
    }
}

void tilt_north() {
    for (int n = 0; n < N; ++n)
        for (int i = 0; i + 1 < N; ++i)
            for (int j = 0; j < N; ++j)
                if (grid[i][j] == '.' && grid[i + 1][j] == 'O')
                    std::swap(grid[i][j], grid[i + 1][j]);
}

void rotate_cw() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            tmp[j][N - i - 1] = grid[i][j];
    memcpy(grid, tmp, N * N);
}

int north_load() {
    int result = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (grid[i][j] == 'O')
                result += N - i;
    return result;
}

long long hash() {
    long long result = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 'O') result += 1;
            if (grid[i][j] == '#') result += 2;
            result *= 3;
        }
    return result;
}

int main() {
    read_input();

    ind[hash()] = 0;
    loads.push_back(north_load());

    tilt_north();
    printf("%d\n", north_load());
    
    while (true) {
        for (int i = 0; i < 4; ++i) {
            tilt_north();
            rotate_cw();
        }
        if (ind.count(hash())) break;
        ind[hash()] = loads.size();
        loads.push_back(north_load());
    }
    
    int cycle_begin = ind[hash()];
    int cycle_length = loads.size() - cycle_begin;
    printf("%d\n", loads[cycle_begin + (STEPS - cycle_begin) % cycle_length]);
}
