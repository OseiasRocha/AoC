#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>

void part1()
{
    std::ifstream file("../input.txt");
    if(!file.is_open()){
        std::cerr << "Failed to open file\n";
    }

    std::string line;
    int sum = 0;
    while(std::getline(file, line))
    {
        int num = 0;
        num = (*std::find_if(line.begin(), line.end(), [](char c){return std::isdigit(c);}) - '0') * 10;
        num += *std::find_if(line.rbegin(), line.rend(), [](char c){return std::isdigit(c);}) - '0';
        sum += num;
    }

    std::cout << sum << "\n";
}

void part2()
{
    std::map<std::string, int> nums {{"one", 1},
    { "two", 2 }, { "three", 3 }, { "four", 4 }, { "five", 5 }, { "six", 6 }, { "seven", 7 }, { "eight", 8 }, { "nine", 9 }};
    std::ifstream file("../input.txt");
    if(!file.is_open()){
        std::cerr << "Failed to open file\n";
    }

    std::string line;
    int sum = 0;
    while(std::getline(file, line))
    {
        auto firstIter = std::find_if(line.begin(), line.end(), [](char c){return std::isdigit(c);});
        int first = *firstIter- '0';
        auto secIter = std::find_if(line.rbegin(), line.rend(), [](char c){return std::isdigit(c);});
        int last = *secIter - '0';
        int firstPos = std::distance(line.begin(), firstIter);
        int lastPos = std::distance(line.begin(), (secIter+1).base());
        for(const auto& [number, num] : nums){
            int f = line.find(number);
            int l = line.rfind(number);
            if(f != std::string::npos && f < firstPos)
            {
                first = num;
                firstPos = f;
            }
            if(l != std::string::npos && l > lastPos)
            {
                last = num;
                lastPos = l;
            }
        }
        sum += (first * 10) + last;
    }

    std::cout << sum << "\n";
}

int main() {

    part1();
    part2();

    return 0;
}
