#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <set>

void part1(const std::vector<std::string>& matrix)
{
    std::regex pattern("[0-9]+");
    int sum = 0;

    for(int i = 0; i < matrix.size(); i++)
    {
        std::sregex_iterator matchesBegin(matrix[i].begin(), matrix[i].end(), pattern);

        for(auto& it = matchesBegin; it != std::sregex_iterator(); it++)
        {
            std::string str = (*it).str();
            int up = i > 0 ? i - 1 : i;
            int down = i < matrix.size() - 1 ? i + 1 : i;
            int left = (*it).position() > 0 ? (*it).position() - 1 : (*it).position();
            int right = (*it).length() + (*it).position() < matrix[i].length() ? (*it).length() + (*it).position() : (*it).length() + (*it).position() - 1;

            for(; left <= right; left++)
            {
                if(matrix[up][left] != '.' && !std::isdigit(matrix[up][left]) ||
                   matrix[down][left] != '.' && !std::isdigit(matrix[down][left]) ||
                   matrix[i][left] != '.' && !std::isdigit(matrix[i][left]))
                {
//                    std::cout << "Found: " << (*it).str() << "\n";
                    sum += std::stoi((*it).str());
                }
            }

        }
    }
    std::cout << sum << "\n";
}

void part2(const std::vector<std::string>& matrix)
{
    std::regex pattern("[0-9]+");
    std::map<std::pair<int, int>, std::set<int>> allStartsAdjacent;
    int sum = 0;

    for(int i = 0; i < matrix.size(); i++)
    {
        std::sregex_iterator matchesBegin(matrix[i].begin(), matrix[i].end(), pattern);

        for(auto& it = matchesBegin; it != std::sregex_iterator(); it++)
        {
            std::string str = (*it).str();
            int up = i > 0 ? i - 1 : i;
            int down = i < matrix.size() - 1 ? i + 1 : i;
            int left = (*it).position() > 0 ? (*it).position() - 1 : (*it).position();
            int right = (*it).length() + (*it).position() < matrix[i].length() ? (*it).length() + (*it).position() : (*it).length() + (*it).position() - 1;
            int posInLine = matrix[i].find('*',left);
            int posUpLine = matrix[up].find('*',left);
            int posDownLine = matrix[down].find('*',left);

            if(posInLine != std::string::npos && posInLine <= right)
            {
                allStartsAdjacent[std::pair<int, int>(i, posInLine)].insert(std::stoi(str));
            }
            if(posUpLine != std::string::npos && posUpLine <= right)
            {
                allStartsAdjacent[std::pair<int, int>(up, posUpLine)].insert(std::stoi(str));
            }
            if(posDownLine != std::string::npos && posDownLine <= right)
            {
                allStartsAdjacent[std::pair<int, int>(down, posDownLine)].insert(std::stoi(str));
            }
        }
    }

    for(const auto& [key, set] : allStartsAdjacent)
    {
        if(set.size() > 1)
        {
            int mult = 1;
            for(const auto& num : set)
            {
                mult *= num;
            }
            sum += mult;
        }
    }
    std::cout << sum;
}

int main() {
    std::fstream file("../input.txt");
    if(file.fail())
    {
        std::cerr << "Failed to open file ";
    }
    std::string line;
    std::vector<std::string> matrix;
    while(std::getline(file, line))
    {
        matrix.push_back(line);
    }

    part1(matrix);
    part2(matrix);

    return 0;
}