#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <array>

std::vector<char> cards{'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

std::vector<char> cardsP2{'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};

enum class Hands {
    INVALID = 0,
    HIGH_CARD = 1,
    ONE_PAIR,
    TWO_PAIR,
    THREE,
    FULL_HOUSE,
    FOUR,
    FIVE
};

struct Hand {
    std::string hand;
    uint64_t bid;
};

Hands evaluate(Hand a) {
    Hands valueA = Hands::INVALID;
    for (const auto &c: cards) {
        int count = std::count(a.hand.begin(), a.hand.end(), c);
        switch (count) {
            case 1:
                valueA > Hands::HIGH_CARD ? valueA = valueA : valueA = Hands::HIGH_CARD;
                break;
            case 2:
                if (valueA == Hands::ONE_PAIR) valueA = Hands::TWO_PAIR;
                else if (valueA == Hands::THREE) valueA = Hands::FULL_HOUSE;
                else
                    valueA > Hands::ONE_PAIR ? valueA = valueA : valueA = Hands::ONE_PAIR;
                break;
            case 3:
                if (valueA == Hands::ONE_PAIR) valueA = Hands::FULL_HOUSE;
                else
                    valueA > Hands::THREE ? valueA = valueA : valueA = Hands::THREE;
                break;
            case 4:
                valueA > Hands::FOUR ? valueA = valueA : valueA = Hands::FOUR;
                break;
            case 5:
                valueA > Hands::FIVE ? valueA = valueA : valueA = Hands::FIVE;
                break;
        }
    }
    return valueA;
}

Hands evaluateP2(Hand a) {
    Hands valueA = Hands::INVALID;
    for (const auto &c: cards) {
        if (c == 'J') continue;
        int count = std::count(a.hand.begin(), a.hand.end(), c);
        switch (count) {
            case 1:
                valueA > Hands::HIGH_CARD ? valueA = valueA : valueA = Hands::HIGH_CARD;
                break;
            case 2:
                if (valueA == Hands::ONE_PAIR) valueA = Hands::TWO_PAIR;
                else if (valueA == Hands::THREE) valueA = Hands::FULL_HOUSE;
                else
                    valueA > Hands::ONE_PAIR ? valueA = valueA : valueA = Hands::ONE_PAIR;
                break;
            case 3:
                if (valueA == Hands::ONE_PAIR) valueA = Hands::FULL_HOUSE;
                else
                    valueA > Hands::THREE ? valueA = valueA : valueA = Hands::THREE;
                break;
            case 4:
                valueA > Hands::FOUR ? valueA = valueA : valueA = Hands::FOUR;
                break;
            case 5:
                valueA > Hands::FIVE ? valueA = valueA : valueA = Hands::FIVE;
                break;
        }
    }

    int count = std::count(a.hand.begin(), a.hand.end(), 'J');
    if (count > 0) {
        switch (valueA) {
            case Hands::HIGH_CARD:
                count == 1 ? valueA = Hands::ONE_PAIR : count == 2 ? valueA = Hands::THREE : count == 3 ? valueA = Hands::FOUR : count ==
                                                                                                               4
                                                                                                               ? valueA = Hands::FIVE
                                                                                                               : valueA = valueA;
                break;
            case Hands::ONE_PAIR:
                count == 1 ? valueA = Hands::THREE : count == 2 ? valueA = Hands::FOUR : count == 3 ? valueA = Hands::FIVE
                                                                                           : valueA = valueA;
                break;
            case Hands::TWO_PAIR:
                count == 1 ? valueA = Hands::FULL_HOUSE : valueA = valueA;
                break;
            case Hands::THREE:
                count == 1 ? valueA = Hands::FOUR : count == 2 ? valueA = Hands::FIVE : valueA = valueA;
                break;
            case Hands::FOUR:
                count == 1 ? valueA = Hands::FIVE : valueA = valueA;
                break;
            case Hands::INVALID:
                valueA = Hands::FIVE;
                break;
        }
    }
    return valueA;
}

void part1() {
    std::vector<Hand> hands;
    std::fstream file("../input.txt");
    std::string line;
    while (getline(file, line)) {
        Hand hand;
        hand.hand = line.substr(0, line.find(' '));
        hand.bid = std::stoull(line.substr(line.find(' ') + 1));
        hands.push_back(hand);
    }

    std::sort(hands.begin(), hands.end(), [](const Hand &a, const Hand &b) {
        Hands valueA = Hands::INVALID, valueB = Hands::INVALID;
        valueA = evaluate(a);
        valueB = evaluate(b);
        if (valueA < valueB) return true;
        else if (valueA == valueB) {
            for (int i = 0; i < a.hand.size(); i++) {
                int findA = std::distance(cards.begin(), std::find(cards.begin(), cards.end(), a.hand[i]));
                int findB = std::distance(cards.begin(), std::find(cards.begin(), cards.end(), b.hand[i]));
                if (findA == findB) continue;
                return findA < findB;
            }
        } else
            return false;
    });
    uint64_t result = 0;
    for (int i = 0; i < hands.size(); i++) {
        result += hands[i].bid * (i + 1);
    }
    std::cout << result << "\n";
}

void part2() {
    std::vector<Hand> hands;
    std::fstream file("../input.txt");
    std::string line;
    while (getline(file, line)) {
        Hand hand;
        hand.hand = line.substr(0, line.find(' '));
        hand.bid = std::stoull(line.substr(line.find(' ') + 1));
        hands.push_back(hand);
    }

    std::sort(hands.begin(), hands.end(), [](const Hand &a, const Hand &b) {
        Hands valueA = Hands::INVALID, valueB = Hands::INVALID;
        valueA = evaluateP2(a);
        valueB = evaluateP2(b);
        if (valueA < valueB) return true;
        else if (valueA == valueB) {
            for (int i = 0; i < a.hand.size(); i++) {
                int findA = std::distance(cardsP2.begin(), std::find(cardsP2.begin(), cardsP2.end(), a.hand[i]));
                int findB = std::distance(cardsP2.begin(), std::find(cardsP2.begin(), cardsP2.end(), b.hand[i]));
                if (findA == findB) continue;
                return findA < findB;
            }
        } else
            return false;
    });
    uint64_t result = 0;
    for (int i = 0; i < hands.size(); i++) {
        result += hands[i].bid * (i + 1);
    }
    std::cout << result << "\n";
}

int main() {

    part1();
    part2();
    return 0;
}
