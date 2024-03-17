#include <iostream>
#include <bitset>
#include <map>
#include <vector>

const int MAX_N = 1500;

int n;

std::vector<int> adj[MAX_N];

std::map<int, int> cap[MAX_N];
std::bitset<MAX_N> visited;

int to_int(std::string s) {
    static std::map<std::string, int> map;
    if (!map.count(s)) return map[s] = n++;
    else return map[s];
}

void read_input() {
    std::string src, tmp;
    while (std::cin >> tmp) {
        if (tmp.back() == ':') {
            src = tmp;
            src.pop_back();
        } else {
            adj[to_int(src)].push_back(to_int(tmp));
            adj[to_int(tmp)].push_back(to_int(src));
        }
    }
}

void reset_capacity() {
    for (int i = 0; i < n; ++i)
        for (int j : adj[i]) {
            cap[i][j] = 1;
        }
}

bool augment(int i, int sink) {
    if (i == sink) return true;
    visited.set(i);
    for (int j : adj[i])
        if (!visited.test(j) && cap[i][j] > 0 && augment(j, sink)) {
            --cap[i][j];
            ++cap[j][i];
            return true;
        }
    return false;
}

int main() {
    read_input();

    for (int i = 1; i < n; ++i) {
        reset_capacity();
        int flow = 0;
        while (flow <= 3 && augment(0, i)) {
            ++flow;
            visited.reset();
        }
        if (flow == 3) {
            std::cout << visited.count() * (n - visited.count()) << std::endl;
        }
    }
}
