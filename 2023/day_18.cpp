#include <cstdio>
#include <cmath>
#include <vector>

struct coord { long long x, y; };
std::vector<coord> points, points_2;

void read_input() {
    coord pos = {0, 0}, pos_2 = {0, 0};
    char dir; int steps, color;
    while (scanf("%c %d (#%x)\n", &dir, &steps, &color) == 3) {
        if (dir == 'R') pos.x += steps;
        if (dir == 'D') pos.y += steps;
        if (dir == 'L') pos.x -= steps;
        if (dir == 'U') pos.y -= steps;
        points.push_back(pos);
        if (color % 16 == 0) pos_2.x += color / 16;
        if (color % 16 == 1) pos_2.y += color / 16;
        if (color % 16 == 2) pos_2.x -= color / 16;
        if (color % 16 == 3) pos_2.y -= color / 16;
        points_2.push_back(pos_2);
    }
}

long long signed_area(coord a, coord b, coord c) {
    return (a.x - b.x) * (a.y + b.y) + (b.x - c.x) * (b.y + c.y) + (c.x - a.x) * (c.y + a.y);
}

long long solve(std::vector<coord> const &points) {
    long long result = 0;
    for (int i = 1; i + 1 < points.size(); ++i)
        result += signed_area(points[0], points[i], points[i + 1]);
    if (result < 0) result = -result;
    for (int i = 0; i < points.size(); ++i) {
        result += std::abs(points[i].x - points[(i + 1) % points.size()].x);
        result += std::abs(points[i].y - points[(i + 1) % points.size()].y);
    }
    return result / 2 + 1;
}

int main() {
    read_input();
    printf("%lld\n", solve(points));
    printf("%lld\n", solve(points_2));
}
