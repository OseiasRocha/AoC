#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <functional>

void part1() {
    std::fstream file("../input.txt");

    if (file.is_open()) {
        std::string line;
        std::vector<std::vector<int>> win;
        std::vector<std::vector<int>> have;
        while (std::getline(file, line)) {
            int pos = line.find(": ");
            std::stringstream first(line.substr(pos + 1, line.find('|') - pos - 1));
            std::stringstream second(line.substr(line.find('|') + 1));
            win.emplace_back(std::istream_iterator<int>(first), std::istream_iterator<int>());
            have.emplace_back(std::istream_iterator<int>(second), std::istream_iterator<int>());
        }
        int sum = 0;
        for (int i = 0; i < have.size(); i++) {

            int count = 0;
            for (int j = 0; j < have[i].size(); j++) {
                if (std::any_of(win[i].begin(), win[i].end(), [&have, &i, &j](int num) { return num == have[i][j]; })) {
                    count++;
                }
            }
            if (count > 0) {
                sum += 1 << (count - 1);
            }
        }
        std::cout << "sum: " << sum << "\n";
    }
}

struct Card {
    std::vector<int> win;
    std::vector<int> have;
    int multiplier = 1;
};

void part2() {
    std::fstream file("../input.txt");

    if (file.is_open()) {
        std::string line;
        std::vector<Card> cards;
        while (std::getline(file, line)) {
            int pos = line.find(": ");
            std::stringstream first(line.substr(pos + 1, line.find('|') - pos - 1));
            std::stringstream second(line.substr(line.find('|') + 1));
            Card card;
            card.win = std::vector<int>(std::istream_iterator<int>(first), std::istream_iterator<int>());
            card.have = std::vector<int>(std::istream_iterator<int>(second), std::istream_iterator<int>());
            cards.push_back(card);
        }
        int sum = 0;
        for (int i = 0; i < cards.size(); i++) {


            for (int mult = 0; mult < cards[i].multiplier; mult++) {
                int count = 0;
                for (int j = 0; j < cards[i].have.size(); j++) {
                    if (std::any_of(cards[i].win.begin(), cards[i].win.end(),
                                    [&cards, &i, &j](int num) { return num == cards[i].have[j]; })) {
                        count++;
                    }
                }
                for (int k = i + 1; k < i + count + 1; k++) {
                    cards[k].multiplier++;
                }
            }

        }
        for (const auto& card: cards) {
            sum += card.multiplier;
        }
        std::cout << "sum: " << sum;
    }
}

int main() {

    part1();
    part2();
    return 0;
}