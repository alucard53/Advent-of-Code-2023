#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string.h>
#include <unordered_map>
#include <vector>

std::vector<std::vector<int>> dirs = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
};

std::unordered_map<char, int> slope = {
    {'^', 0},
    {'v', 1},
    {'<', 2},
    {'>', 3},
};

int max_steps = 0;

void dfs(std::vector<std::string>& grid) {
    std::stack<std::vector<int>> stack;
    stack.push({0, 1, 0, 1, 0});

    while (!stack.empty()) {
        auto curr = stack.top();
        stack.pop();
        int i = curr[0];
        int j = curr[1];
        int prev_i = curr[2];
        int prev_j = curr[3];
        int steps = curr[4];

        if (i == static_cast<int>(grid.size() - 1) and
            j == static_cast<int>(grid[0].size() - 2)) {
            max_steps = std::max(max_steps, steps);
            continue;
        }

        if (slope.find(grid[i][j]) != slope.end()) {
            int dir = slope[grid[i][j]];
            int m = i + dirs[dir][0];
            int n = j + dirs[dir][1];

            if (m == prev_i and n == prev_j) {
                continue;
            }

            stack.push({m, n, i, j, steps + 1});
        } else {
            for (auto dir : dirs) {
                int m = i + dir[0];
                int n = j + dir[1];

                if (m == prev_i and n == prev_j) {
                    continue;
                }

                if (0 <= m and m < static_cast<int>(grid.size()) and 0 <= n and
                    n < static_cast<int>(grid[0].size()) and
                    grid[m][n] != '#') {
                    stack.push({m, n, i, j, steps + 1});
                }
            }
        }
    }
}

int main() {
    std::fstream f("input.txt");
    std::string input;
    std::ostringstream oss;

    oss << f.rdbuf();
    input = oss.str();
    f.close();

    std::vector<std::string> grid;

    std::string curr = "";
    for (char i : input) {
        if (i == '\n') {
            grid.push_back(curr);
            curr = "";
        } else {
            curr += i;
        }
    }

    for (auto i : grid) {
        std::cout << i << "\n";
    }

    dfs(grid);
    std::cout << max_steps;

    return 0;
}
