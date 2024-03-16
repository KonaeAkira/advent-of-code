#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <queue>
#include <algorithm>
#include <array>

const int N = 131;
const int STEPS = 26501365;
const int K = (STEPS - N / 2) / N;

static_assert(N % 2 == 1);
static_assert(N / 2 % 2 == 1);
static_assert((STEPS - N / 2) % N == 0);

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

char grid[N][N];
long long inner[2], outer[2], offset[2];

void read_input() {
    char tmp[N + 1];
    for (int i = 0; i < N; ++i) {
        scanf("%s\n", tmp);
        memcpy(grid[i], tmp, N);
    }
    grid[N / 2][N / 2] = '.';
}

int count(int max_distance, bool wrap_around = true) {
    int result[2] = {0, 0};
    std::queue<std::pair<int, int>> queue, next;
    std::set<std::pair<int, int>> visited;
    next.emplace(N / 2, N / 2);
    visited.emplace(N / 2, N / 2);
    for (int current_distance = 0; current_distance <= max_distance; ++current_distance) {
        for (std::swap(queue, next); !queue.empty(); queue.pop()) {
            int x = queue.front().first, y = queue.front().second;
            ++result[current_distance % 2];
            for (int i = 0; i < 4; ++i) {
                int a = x + dx[i], b = y + dy[i];
                if (!wrap_around && (a < 0 || a >= N || b < 0 || b >= N))
                    continue;
                if (!visited.count({a, b}) && grid[(a % N + N) % N][(b % N + N) % N] == '.') {
                    next.emplace(a, b);
                    visited.emplace(a, b);
                }
            }
        }
    }
    return result[max_distance % 2];
}

long long magic(int k) {  // N/2 + k*N steps
    long long a[3] = {1, 0, 0};
    for (int i = 1; i <= k; ++i) {
        a[i % 2] += i * 4;
        a[2] += i * 2;
    }
    return a[0] * inner[!(k % 2)] + a[1] * inner[k % 2] + a[2] * (outer[0] + outer[1]);
}

int main() {
    read_input();

    inner[0] = count(N / 2 - 1);
    inner[1] = count(N / 2);
    outer[0] = count(N - 1, false) - inner[0];
    outer[1] = count(N - 2, false) - inner[1];

    offset[0] = (magic(2) - count(N / 2 + 2 * N)) / 2;
    offset[1] = magic(1) - count(N / 2 + N);

    // for (int i = 0; i < 7; ++i)
    //     printf("k=%d %lld %lld\n", i, count(N / 2 + i * N), magic(i) - i * offset[i % 2]);

    printf("%d\n", count(64));
    printf("%lld\n", magic(K) - K * offset[K % 2]);
}
