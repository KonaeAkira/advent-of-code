#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

std::string s;
std::map<std::string, std::pair<std::string, std::string>> map;

void read_input() {
    char buf[1024];
    scanf("%s\n", buf); s = buf;
    char a[4], b[4], c[4];
    while (scanf("%s = (%[^,], %[^)])\n", a, b, c) == 3) map[a] = {b, c};
}

int steps(std::string cur, std::function<bool(std::string)> is_target) {
    int result = 0;
    while (!is_target(cur)) cur = (s[result++ % s.size()] == 'L' ? map[cur].first : map[cur].second);
    return result;
}

int main() {
    read_input();
    printf("%d\n", steps("AAA", [](std::string const &s) { return s == "ZZZ"; }));
    long long part_2 = 1;
    for (auto p : map)
        if (p.first[2] == 'A')
            part_2 = std::lcm(part_2, steps(p.first, [](std::string const &s) { return s[2] == 'Z'; }));
    printf("%lld\n", part_2);
}
