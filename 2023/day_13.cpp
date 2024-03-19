#include <cstdio>
#include <cstring>
#include <bitset>

const int MAX_N = 64;

int n, m;
char grid[MAX_N][MAX_N];

bool read_input() {
    n = 0;
    scanf(" ");
    while (scanf("%[^\n]%*c", grid[n]) == 1) ++n;
    m = strlen(grid[0]);
    return n != 0;
}

void find_vert_axis(std::bitset<MAX_N * 2> &bitset) {
    for (int k = 1; k < m; ++k) {
        for (int i = 0; i < n; ++i)
            for (int d = 0; k - d - 1 >= 0 && k + d < m; ++d)
                if (grid[i][k - d - 1] != grid[i][k + d]) goto skip_v;
        bitset.set(k);
    skip_v:
        continue;
    }
}

void find_hori_axis(std::bitset<MAX_N * 2> &bitset) {
    for (int k = 1; k < n; ++k) {
        for (int j = 0; j < m; ++j)
            for (int d = 0; k - d - 1 >= 0 && k + d < n; ++d)
                if (grid[k - d - 1][j] != grid[k + d][j]) goto skip_h;
        bitset.set(MAX_N + k);
    skip_h:
        continue;
    }
}

std::bitset<MAX_N * 2> find_axis() {
    std::bitset<MAX_N * 2> result;
    find_vert_axis(result);
    find_hori_axis(result);
    return result;
}

int score(std::bitset<MAX_N * 2> const &bitset) {
    int result = 0;
    for (int i = 0; i < MAX_N; ++i) {
        if (bitset.test(i)) result += i;
        if (bitset.test(MAX_N + i)) result += 100 * i;
    }
    return result;
}

int main() {
    int part_1 = 0, part_2 = 0;
    while (read_input()) {
        std::bitset<MAX_N * 2> prv = find_axis(), nxt;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                grid[i][j] = (grid[i][j] ^ '.' ^ '#');
                nxt = find_axis();
                grid[i][j] = (grid[i][j] ^ '.' ^ '#');
                if (nxt.any() && nxt != prv) goto found;
            }
    found:
        part_1 += score(prv);
        part_2 += score(nxt) - score(nxt & prv);
    }
    printf("%d\n", part_1);
    printf("%d\n", part_2);
}