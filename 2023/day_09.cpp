#include <cstdio>
#include <vector>

std::vector<int> read_input() {
    std::vector<int> result;
    int x; char c;
    do {
        if (scanf("%d%c", &x, &c) != 2) break;
        result.push_back(x);
    } while (c != '\n');
    return result;
}

bool all_zero(std::vector<int> &vec) {
    for (int x : vec) if (x != 0) return false;
    return true;
}

int next(std::vector<int> &vec) {
    if (all_zero(vec)) return 0;
    std::vector<int> dif;
    for (int i = 0; i + 1 < vec.size(); ++i)
        dif.push_back(vec[i + 1] - vec[i]);
    return vec.back() + next(dif);
}

int main() {
    int part_1 = 0, part_2 = 0;
    std::vector<int> vec;
    while (!(vec = read_input()).empty()) {
        part_1 += next(vec);
        for (int i = 0; i < vec.size() / 2; ++i)
            std::swap(vec[i], vec[vec.size() - 1 - i]);
        part_2 += next(vec);
    }
    printf("%d\n", part_1);
    printf("%d\n", part_2);
}
