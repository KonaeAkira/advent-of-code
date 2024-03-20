#include <cstdio>
#include <cstring>
#include <vector>

const char *num[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

bool is_num(char *buf, int n) {
    if (buf[0] == '0' + n) return true;
    for (int i = 0; i < strlen(num[n]); ++i)
        if (buf[i] != num[n][i]) return false;
    return true;
}

int main() {
    int part_1 = 0, part_2 = 0;
    char buf[128];
    while (scanf("%s\n", buf) == 1) {
        std::vector<int> v;
        for (int i = 0; i < strlen(buf); ++i)
            if (buf[i] >= '0' && buf[i] <= '9') v.push_back(buf[i] - '0');
        part_1 += v.front() * 10 + v.back(); v.clear();
        for (int i = 0; i < strlen(buf); ++i)
            for (int j = 0; j < 10; ++j)
                if (is_num(buf + i, j)) v.push_back(j);
        part_2 += v.front() * 10 + v.back();
    }
    printf("%d\n%d\n", part_1, part_2);
}
