#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

struct Node {
    Node(std::string label) : label(label) {}

    std::string label;
    Node *leftNode;
    Node *rightNode;
};

void part1() {
    std::fstream file("../input.txt");
    std::string line;
    std::unordered_map<std::string, Node *> nodes;
    std::string instructions;
    std::getline(file, instructions);
    while (std::getline(file, line)) {
        if (line.length() > 1) {
            std::string label = line.substr(0, line.find(" = "));
            std::string left = line.substr(line.find('(') + 1, line.find(',') - 1 - line.find('('));
            std::string right = line.substr(line.find(',') + 2, line.find(')') - line.find(',') - 2);

            if (nodes.find(label) == nodes.end()) {
                Node *node = new Node(label);
                nodes[label] = node;
            }
            if (nodes.find(left) == nodes.end()) {
                Node *node = new Node(left);
                nodes[left] = node;
            }
            if (nodes.find(right) == nodes.end()) {
                Node *node = new Node(right);
                nodes[right] = node;
            }

            nodes[label]->leftNode = nodes[left];
            nodes[label]->rightNode = nodes[right];
        }
    }
    Node *node = nodes["AAA"];
    bool found = false;
    uint64_t steps = 0;
    while (!found) {
        for (const auto &instr: instructions) {
            steps++;
            if (instr == 'R') {
                node = nodes[node->label]->rightNode;
                if (node->label == "ZZZ") {
                    found = true;
                    break;
                }
            } else {
                node = nodes[node->label]->leftNode;
                if (node->label == "ZZZ") {
                    found = true;
                    break;
                }
//                std::cout << "Left\n";
            }
        }
    }
    std::cout << steps << "\n";
}

void part2() {
    std::fstream file("../input.txt");
    std::string line;
    std::map<std::string, Node *> nodes;
    std::string instructions;
    std::getline(file, instructions);
    while (std::getline(file, line)) {
        if (line.length() > 1) {
            std::string label = line.substr(0, line.find(" = "));
            std::string left = line.substr(line.find('(') + 1, line.find(',') - 1 - line.find('('));
            std::string right = line.substr(line.find(',') + 2, line.find(')') - line.find(',') - 2);

            if (nodes.find(label) == nodes.end()) {
                Node *node = new Node(label);
                nodes[label] = node;
            }
            if (nodes.find(left) == nodes.end()) {
                Node *node = new Node(left);
                nodes[left] = node;
            }
            if (nodes.find(right) == nodes.end()) {
                Node *node = new Node(right);
                nodes[right] = node;
            }

            nodes[label]->leftNode = nodes[left];
            nodes[label]->rightNode = nodes[right];
        }
    }

    std::vector<Node *> paths;
    auto currNode = nodes.begin();
    while (true) {
        auto node = std::find_if(currNode, nodes.end(), [](std::pair<std::string, Node *> n) {
            return n.first[2] == 'A';
        });
        currNode = node;
        if (currNode == nodes.end()) break;
        currNode++;
        paths.push_back(node->second);
    }
    std::vector<uint64_t> stepsVec;
    for (auto &node: paths) {
        bool found = false;
        uint64_t steps = 0;
        while (!found) {
            for (const auto &instr: instructions) {
                steps++;
                if (instr == 'R') {
                    node = nodes[node->label]->rightNode;
                    if (node->label[2] == 'Z') {
                        found = true;
                        break;
                    }
                } else {
                    node = nodes[node->label]->leftNode;
                    if (node->label[2] == 'Z') {
                        found = true;
                        break;
                    }
//                std::cout << "Left\n";
                }
            }
        }
        stepsVec.push_back(steps);

    }
    uint64_t steps = std::lcm(stepsVec[0], stepsVec[1]);
    for (int i = 2; i < stepsVec.size(); i++) {
        steps = std::lcm(steps, stepsVec[i]);
    }
    std::cout << steps << "\n";
}

int main() {
    part1();
    part2();
    return 0;
}
