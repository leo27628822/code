// 10927143 王胤迦
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main() {
    std::vector<std::string> names;
    std::vector<int> scores;
    std::ifstream ifs("input3.txt", std::ios::in);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else {
        std::string name;
        int score;
        while (ifs >> name >> score) {
            cout << name << " " << score << "\n";
            names.push_back(name);
            scores.push_back(score);
        }
        ifs.close();
    }
    ifs.close();
    return 0;
}
}
