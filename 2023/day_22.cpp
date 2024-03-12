#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

const int INF = 1e9;

const int MAX_X = 10;
const int MAX_Y = 10;

struct Box {
    int x1, y1, z1, x2, y2, z2;
};

int height_map[MAX_X][MAX_Y];

std::vector<Box> boxes;

std::vector<std::vector<int>> adj;
std::vector<bool> visited;

void read_input() {
    int x1, y1, z1, x2, y2, z2;
    while (scanf("%d,%d,%d~%d,%d,%d\n", &x1, &y1, &z1, &x2, &y2, &z2) == 6) {
        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);
        if (z1 > z2) std::swap(z1, z2);
        boxes.push_back({x1, y1, z1, x2, y2, z2});
    }
}

int count(int i, int removed) {
    visited[i] = true;
    if (i == removed) return 1;
    int result = 1;
    for (int j : adj[i])
        if (!visited[j]) {
            result += count(j, removed);
        }
    return result;
}

void construct_graph() {
    std::sort(boxes.begin(), boxes.end(), [](const Box &lhs, const Box &rhs) {
        return lhs.z1 < rhs.z1;
    });
    adj.resize(boxes.size());
    for (int i = 1; i < boxes.size(); ++i) {
        int height = -INF;
        std::set<int> supports;
        for (int x = boxes[i].x1; x <= boxes[i].x2; ++x)
            for (int y = boxes[i].y1; y <= boxes[i].y2; ++y) {
                if (boxes[height_map[x][y]].z2 > height) {
                    height = boxes[height_map[x][y]].z2;
                    supports.clear();
                }
                if (boxes[height_map[x][y]].z2 == height) {
                    supports.insert(height_map[x][y]);
                }
            }
        for (int j : supports) {
            adj[j].push_back(i);
        }
        boxes[i].z2 = boxes[i].z2 - boxes[i].z1 + height + 1;
        boxes[i].z1 = height + 1;
        for (int x = boxes[i].x1; x <= boxes[i].x2; ++x)
            for (int y = boxes[i].y1; y <= boxes[i].y2; ++y)
                height_map[x][y] = i;
    }
}

int main() {
    boxes.push_back({-INF, -INF, -INF, INF, INF, -1});
    read_input();

    construct_graph();

    visited.resize(boxes.size());
    std::vector<int> reachable;
    for (int i = 0; i < boxes.size(); ++i) {
        visited.assign(visited.size(), false);
        reachable.push_back(count(0, i));
    }

    int part_1 = 0, part_2 = 0;
    for (int i = 1; i < boxes.size(); ++i) {
        if (reachable[i] == boxes.size()) ++part_1;
        part_2 += boxes.size() - reachable[i];
    }
    printf("%d\n%d\n", part_1, part_2);
}
