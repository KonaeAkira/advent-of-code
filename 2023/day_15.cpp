#include <cstdio>
#include <vector>
#include <string>

std::vector<std::string> strings;
std::vector<std::pair<std::string, int>> boxes[256];

void read_input() {
    char buffer[1024];
    while (scanf("%[^,\n]%*[,\n]", buffer) == 1)
        strings.emplace_back(buffer);
}

int hash(std::string const &s) {
    int result = 0;
    for (char c : s) result = (result + c) * 17 % 256;
    return result;
}

void insert(std::string s, int v) {
    auto &box = boxes[hash(s)];
    for (auto &p : box)
        if (p.first == s) {
            p.second = v;
            return;
        }
    box.emplace_back(s, v);
}

void remove(std::string s) {
    auto &box = boxes[hash(s)];
    for (auto it = box.begin(); it != box.end(); ++it)
        if (it->first == s) {
            box.erase(it);
            return;
        }
}

int main() {
    read_input();

    int part_1 = 0;
    for (auto const &s : strings)
        part_1 += hash(s);
    printf("%d\n", part_1);

    char label[1024]; int value;
    for (auto const &s : strings)
        if (s.back() == '-') {
            remove(s.substr(0, s.size() - 1));
        } else {
            sscanf(s.c_str(), "%[^=]=%d", label, &value);
            insert(label, value);
        }
    
    int part_2 = 0;
    for (int i = 0; i < 256; ++i)
        for (int j = 0; j < boxes[i].size(); ++j)
            part_2 += (i + 1) * (j + 1) * boxes[i][j].second;
    printf("%d\n", part_2);
}
