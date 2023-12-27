#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <map>
#include <vector>

struct Game {

    Game() = default;

    Game(uint32_t red, uint32_t green, uint32_t blue) : m_red(red), m_green(green),
                                                        m_blue(blue) {}

    ~Game() = default;

    bool operator==(const Game &rhs) const {
        return m_red == rhs.m_red && m_blue == rhs.m_blue && m_green == rhs.m_green;
    }

    bool operator<=(const Game &rhs) const {
        return m_red <= rhs.m_red && m_blue <= rhs.m_blue && m_green <= rhs.m_green;
    }

    friend std::ostream &operator<<(std::ostream &os, const Game &game) {
        os << "Red: " << game.m_red << " Green: " << game.m_green << " Blue: " << game.m_blue;
        return os;
    }


    uint32_t m_red;
    uint32_t m_green;
    uint32_t m_blue;


};

void part1() {
    Game max {12, 13, 14};
    std::ifstream file("../input.txt");
    if (file.fail()) {
        std::cout << "Failed to open file. iostate:  " << file.exceptions();
        return;
    }
    std::string line;
    std::map<uint32_t, std::vector<Game>> allGames;
    while (std::getline(file, line)) {
        uint32_t colon = line.find(':');
        uint32_t space = line.find(' ');
        uint32_t gameId = std::stoi(line.substr(0, colon).substr(space));
        std::stringstream games(line.substr(colon + 1));
        std::string game;
        std::vector<Game> runs;
        while (std::getline(games, game, ';')) {
            std::stringstream runsStr(game);
            std::string run;
            uint32_t red = 0;
            uint32_t green = 0;
            uint32_t blue = 0;
            while (std::getline(runsStr, run, ',')) {
                std::string trimmed = run;
                if (std::isspace(run[0])) {
                    trimmed = run.substr(1);
                }
                if (trimmed.find("red") != std::string::npos) {
                    red = std::stoi(trimmed.substr(0, trimmed.find(' ')));
                } else if (trimmed.find("green") != std::string::npos) {
                    green = std::stoi(trimmed.substr(0, trimmed.find(' ')));
                } else if (trimmed.find("blue") != std::string::npos) {
                    blue = std::stoi(trimmed.substr(0, trimmed.find(' ')));
                }
            }
            runs.emplace_back(red, green, blue);
        }
        allGames[gameId] = runs;

    }
    uint32_t sum = 0;
    for (const auto &[gameId, runs]: allGames) {
        bool possible = true;
        for (const auto &game: runs) {
            if(game.m_red <= max.m_red && game.m_blue <= max.m_blue && game.m_green <= max.m_green)
               possible &= true;
            else
                possible &= false;
        }
        if(possible)
            sum += gameId;
    }
    std::cout << "sum: " << sum << "\n";
}

void part2() {
    std::ifstream file("../input.txt");
    if (file.fail()) {
        std::cout << "Failed to open file. iostate:  " << file.exceptions();
        return;
    }
    std::string line;
    std::map<uint32_t, std::vector<Game>> allGames;
    while (std::getline(file, line)) {
        uint32_t colon = line.find(':');
        uint32_t space = line.find(' ');
        uint32_t gameId = std::stoi(line.substr(0, colon).substr(space));
        std::stringstream games(line.substr(colon + 1));
        std::string game;
        std::vector<Game> runs;
        while (std::getline(games, game, ';')) {
            std::stringstream runsStr(game);
            std::string run;
            uint32_t red = 0;
            uint32_t green = 0;
            uint32_t blue = 0;
            while (std::getline(runsStr, run, ',')) {
                std::string trimmed = run;
                if (std::isspace(run[0])) {
                    trimmed = run.substr(1);
                }
                if (trimmed.find("red") != std::string::npos) {
                    red = std::stoi(trimmed.substr(0, trimmed.find(' ')));
                } else if (trimmed.find("green") != std::string::npos) {
                    green = std::stoi(trimmed.substr(0, trimmed.find(' ')));
                } else if (trimmed.find("blue") != std::string::npos) {
                    blue = std::stoi(trimmed.substr(0, trimmed.find(' ')));
                }
            }
            runs.emplace_back(red, green, blue);
        }
        allGames[gameId] = runs;

    }
    uint32_t sum = 0;
    for (const auto &[gameId, runs]: allGames) {
        uint32_t max_red = 0;
        uint32_t max_blue = 0;
        uint32_t max_green = 0;
        for (const auto &game: runs) {
            max_red < game.m_red ? max_red = game.m_red : max_red = max_red;
            max_blue < game.m_blue ? max_blue = game.m_blue : max_blue = max_blue;
            max_green < game.m_green ? max_green = game.m_green : max_green = max_green;
        }
        sum += max_red * max_blue * max_green;
    }

    std::cout << "sum of the power of these sets: " << sum;
}

int main() {
    part1();
    part2();

    return 0;
}
