#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

#define SRC 1
#define DEST 0
#define RANGE 2

struct Ranges {
    std::vector<std::vector<int64_t>> ranges;
};

int64_t translate(std::vector<Ranges>::iterator mapsIt, int64_t src) {

    if ((*mapsIt).ranges.size() == 0) return src;
    for (const auto &range: (*mapsIt).ranges) {
        if (src <= range[SRC] + range[RANGE] && src >= range[SRC]) {
            return translate(mapsIt + 1, range[DEST] + (std::max(src, range[SRC]) - std::min(src, range[SRC])));
        }
    }
    return translate(mapsIt + 1, src);
//    return src;
}

int64_t translate(std::vector<Ranges>::iterator mapsIt, int64_t src, int64_t len) {

    if ((*mapsIt).ranges.size() == 0) return src;
    for (const auto &range: (*mapsIt).ranges) {
        int64_t inputEnd = src + len;
        int64_t rangeEnd = range[SRC] + range[RANGE];

        int64_t start = std::max(range[SRC], src);
        int64_t end = std::min(inputEnd, rangeEnd);
        int64_t newRange = end - start;

        if(newRange > 0)
        {
            auto locationInRange = translate(mapsIt + 1, start - range[SRC] + range[DEST], newRange);

            if(src < start)
            {
                locationInRange = std::min(locationInRange, translate(mapsIt, src, range[SRC] - src));
            }
            if(inputEnd > end)
            {
                locationInRange = std::min(locationInRange, translate(mapsIt, rangeEnd, inputEnd - rangeEnd));
            }
            return locationInRange;
        }
    }
    return translate(mapsIt + 1, src, len);
//    return src;
}

void part1() {
    std::fstream file("../input.txt");
    std::string line;
    std::vector<uint64_t> seeds;
    std::vector<Ranges> maps;
    while (std::getline(file, line)) {
        if (line.find("seeds: ") != std::string::npos) {
            std::stringstream seedsStream(line.substr(line.find(": ") + 2));
            std::string seed;
            while (seedsStream >> seed) {
                seeds.push_back(std::stoull(seed));
            }
        } else {
            if (line.find(":") != std::string::npos) {
                Ranges ranges;
                while (std::getline(file, line)) {
                    if (line.length() < 2) break;
                    std::stringstream mapStream(line);
                    std::string map;
                    std::vector<int64_t> range;
                    while (mapStream >> map) {
                        range.push_back(std::stoull(map));
                    }
                    ranges.ranges.push_back(range);
                }
                maps.push_back(ranges);
            }
        }
    }
    std::vector<int64_t> locations;
    for (const auto &seed: seeds) {
        locations.push_back(translate(maps.begin(), seed));
    }
    std::cout << *std::min_element(locations.begin(), locations.end()) << "\n";
}

void part2() {
    std::fstream file("../input.txt");
    std::string line;
    std::vector<std::pair<uint64_t, uint64_t>> seeds;
    std::vector<Ranges> maps;
    while (std::getline(file, line)) {
        if (line.find("seeds: ") != std::string::npos) {
            std::stringstream seedsStream(line.substr(line.find(": ") + 2));
            std::string seed;
            std::string range;
            while (!seedsStream.eof()) {
                seedsStream >> seed;
                seedsStream >> range;
                seeds.push_back(std::make_pair(std::stoull(seed), std::stoull(range)));
            }

        } else {
            if (line.find(":") != std::string::npos) {
                Ranges ranges;
                while (std::getline(file, line)) {
                    if (line.length() < 2) break;
                    std::stringstream mapStream(line);
                    std::string map;
                    std::vector<int64_t> range;
                    while (mapStream >> map) {
                        range.push_back(std::stoull(map));
                    }
                    ranges.ranges.push_back(range);
                }
                maps.push_back(ranges);
            }
        }
    }
    std::vector<int64_t> locations;
    for (const auto &[seed, range]: seeds) {
        locations.push_back(translate(maps.begin(), seed, range));
    }
    std::cout << *std::min_element(locations.begin(), locations.end()) << "\n";
}

int main() {
    part1();
    part2();
    return 0;
}
