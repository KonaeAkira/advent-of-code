#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <array>

typedef std::array<std::pair<int, int>, 4> Range;

const Range FULL_RANGE = {{{1, 4001}, {1, 4001}, {1, 4001}, {1, 4001}}};
const Range EMPTY_RANGE = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
const std::map<char, int> prop_map = {{'x', 0}, {'m', 1}, {'a', 2}, {'s', 3}};

struct Rule {
    Range allowed_range, disallowed_range;
    std::string target_workflow;
};

std::map<std::string, std::vector<Rule>> workflows;
std::vector<Range> accepted_ranges, values;

void read_input() {
    char name[16], rules_str[256];
    while (scanf("%[^{]{%[^}]}\n", name, rules_str)) {
        auto &rules = workflows[name];
        int offset = 0, rhs; char prop, op;
        while (sscanf(rules_str + offset, "%c%c%d:%[^,]", &prop, &op, &rhs, name) == 4) {
            Range allowed = FULL_RANGE, disallowed = FULL_RANGE;
            if (op == '<') {
                allowed[prop_map.at(prop)].second = rhs;
                disallowed[prop_map.at(prop)].first = rhs;
            } else {
                allowed[prop_map.at(prop)].first = rhs + 1;
                disallowed[prop_map.at(prop)].second = rhs + 1;
            }
            rules.push_back({allowed, disallowed, name});
            while (rules_str[offset++] != ',');
        }
        sscanf(rules_str + offset, "%s", name);
        rules.push_back({FULL_RANGE, EMPTY_RANGE, name});
    }
    int x, m, a, s;
    while (scanf("{x=%d,m=%d,a=%d,s=%d}\n", &x, &m, &a, &s) == 4) {
        values.push_back({{{x, x + 1}, {m, m + 1}, {a, a + 1}, {s, s + 1}}});
    }
}

Range intersection(Range const &lhs, Range const &rhs) {
    Range result;
    for (int i = 0; i < 4; ++i) {
        result[i].first = std::max(lhs[i].first, rhs[i].first);
        result[i].second = std::min(lhs[i].second, rhs[i].second);
    }
    return result;
}

long long combinations(Range const &range) {
    long long result = 1;
    for (auto const &[lo, hi] : range) {
        if (lo >= hi) return 0;
        result *= hi - lo;
    }
    return result;
}

void dfs(std::string current_workflow, Range current_range) {
    if (current_workflow == "A") accepted_ranges.push_back(current_range);
    for (auto rule : workflows[current_workflow]) {
        dfs(rule.target_workflow, intersection(current_range, rule.allowed_range));
        current_range = intersection(current_range, rule.disallowed_range);
    }
}

int main() {
    read_input();
    dfs("in", FULL_RANGE);

    long long part_1 = 0;
    for (auto value : values) {
        bool accepted = false;
        for (auto range : accepted_ranges) {
            accepted |= combinations(intersection(value, range)) != 0;
        }
        if (accepted) for (auto p : value) part_1 += p.first;
    }
    printf("%lld\n", part_1);

    long long part_2 = 0;
    for (auto range : accepted_ranges)
        part_2 += combinations(range);
    printf("%lld\n", part_2);
}
