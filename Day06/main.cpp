#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

void part1() {
    std::fstream file("../input.txt");
    std::string line;
    std::vector<int> times;
    std::vector<int> distances;
    std::getline(file, line);
    std::stringstream ss(line.substr(line.find(":") + 1));
    std::string num;
    while (ss >> num) {
        times.push_back(std::stoi(num));
    }
    std::getline(file, line);
    std::stringstream ss2(line.substr(line.find(":") + 1));
    while (ss2 >> num) {
        distances.push_back(std::stoi(num));
    }
    int total = 1;
    for (int i = 0; i < times.size(); i++) {
        int count = 0;
        for (int holdTime = 0; holdTime < times[i]; holdTime++) {
            if ((times[i] - holdTime) * holdTime > distances[i]) {
                count++;
            }
        }
        total *= count;
    }
    std::cout << total << "\n";
}

void part2() {
    std::fstream file("../input.txt");
    std::string line;
    std::getline(file, line);
    std::string ss(line.substr(line.find(":") + 1));
    ss.erase(std::remove_if(ss.begin(), ss.end(), isspace), ss.end());
    uint64_t time = std::stoull(ss);
    std::getline(file, line);
    std::string ss2(line.substr(line.find(":") + 1));
    ss2.erase(std::remove_if(ss2.begin(), ss2.end(), isspace), ss2.end());
    uint64_t distance = std::stoull(ss2);
    int total = 1;
    int count = 0;
    for (int holdTime = 0; holdTime < time; holdTime++) {
        if ((time - holdTime) * holdTime > distance) {
            count++;
        }
    }
    total *= count;
    std::cout << total << "\n";
}

int main() {
    part1();
    part2();
    return 0;
}
