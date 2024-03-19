#include <cstdio>
#include <cstring>
#include <vector>

int n;
char s[256];
std::vector<int> vec;

long long f[256][32];

bool read_input() {
    memset(s, 0, sizeof(s));
    scanf("%[^ ] ", s);
    if ((n = strlen(s)) == 0) return false;
    vec.clear(); int x;
    while (scanf("%d%*[,\n]", &x) == 1) vec.push_back(x);
    return true;
}

bool convertible(int pos, char c) {
    return (pos >= n && c == '.') || s[pos] == '?' || s[pos] == c;
}

bool fits_segment(int pos, int len) {
    if (pos > 0 && !convertible(pos - 1, '.')) return false;
    for (int i = pos; i < pos + len; ++i)
        if (!convertible(i, '#')) return false;
    if (pos + len < n && !convertible(pos + len, '.')) return false;
    return true;
}

long long solve() {
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= vec.size(); ++j) {
            if (j < vec.size() && fits_segment(i, vec[j]))
                f[i + vec[j] + 1][j + 1] += f[i][j];
            if (convertible(i, '.'))
                f[i + 1][j] += f[i][j];
        }
    return f[n + 1][vec.size()];
}

void unfold() {
    s[n++] = '?';
    for (int i = n; i < 5 * n; ++i)
        s[i] = s[i % n];
    s[n = 5 * n - 1] = 0;
    int m = vec.size();
    for (int i = m; i < 5 * m; ++i)
        vec.push_back(vec[i % m]);
}

int main() {
    long long part_1 = 0, part_2 = 0;
    while (read_input()) {
        part_1 += solve();
        unfold();
        part_2 += solve();
    }
    printf("%lld\n", part_1);
    printf("%lld\n", part_2);
}