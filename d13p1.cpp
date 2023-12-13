#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vcruntime.h>
#include <vector>

using std::string, std::vector;

int main() {
    std::ifstream file("input.txt");
    int sum = 0;

    while (!file.eof()) {
        vector<string> pattern;
        string line;
        while (std::getline(file, line) and line != "") {
            pattern.push_back(line);
        }

        int m = pattern.size();
        int n = pattern[0].size();
      
        for (int i = 0; i < n - 1; i++) {
            bool mirror;
            int dif = 0;
            for (int x = i, y = i + 1; x >= 0 and y < n; x--, y++) {
                mirror = true;
                for (int z = 0; z < m; z++) {
                    if (pattern[z][x] != pattern[z][y]) {
                        if (dif < 1) {
                            dif++;
                        } else {
                            mirror = false;
                            break;
                        }
                    }
                }
                if (!mirror) {
                    break;
                }
            }
            if (dif == 1 and mirror) {
                sum += i + 1;
                break;
            }
        }

        for (int i = 0; i < m - 1; i++) {
            bool mirror;
            int dif = 0;
            for (int x = i, y = i + 1; x >= 0 and y < m; x--, y++) {
                mirror = true;
                for (int z = 0; z < n; z++) {
                    if (pattern[x][z] != pattern[y][z]) {
                        if (dif < 1) {
                            dif++;
                        } else {
                            mirror = false;
                            break;
                        }
                    }
                }
                if (!mirror) {
                    break;
                }
            }
            if (dif == 1 and mirror) {
                sum += (i + 1) * 100;
                break;
            }
        }

    }
    std::cout << sum;

    file.close();
}
