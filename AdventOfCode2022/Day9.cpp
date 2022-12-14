#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include "utils.h"

#include "Day9.h"

Day9::Day9() {
	day = 9;
	filename = "input/day9.txt";
}

int Day9::puzzle1() {
    fillData();
    pairi head{ 0,0 };
    pairi tail{ 0,0 };
    pairi moveDown{ 1,0 };
    pairi moveUp{ -1,0 };
    pairi moveRight{ 0,1 };
    pairi moveLeft{ 0,-1 };

    visited.insert(tail);
    for (int i = 0; i < movements.size(); i++) {
        auto current = movements[i];
        for (int j = 0; j < times[i]; j++) {
            head = sum(head, current);
            auto htdiff = diff(head, tail);
            if (htdiff == pairi{ -2, 0 }) {
                tail = sum(tail, moveUp);
            }
            else if (htdiff == pairi{ 2, 0 }) {
                tail = sum(tail, moveDown);
            }
            else if (htdiff == pairi{ 0, 2 }) {
                tail = sum(tail, moveRight);
            }
            else if (htdiff == pairi{ 0, -2 }) {
                tail = sum(tail, moveLeft);
            }
            else if (std::abs(htdiff.first) > 1 || std::abs(htdiff.second) > 1) {
                if (htdiff.first < 0) {
                    tail = sum(tail, moveUp);
                }
                else {
                    tail = sum(tail, moveDown);
                }
                if (htdiff.second < 0) {
                    tail = sum(tail, moveLeft);
                }
                else {
                    tail = sum(tail, moveRight);
                }
            }
            visited.insert(tail);
        }
    }
    return visited.size();
}

int Day9::puzzle2() {
    //fillData();
    return 0;
}

void Day9::fillData()
{
    std::ifstream ifs(filename, std::ios::binary);
    std::string line;
    while (getline(ifs, line)) {
        if (line[0] == 'U') { movements.push_back({ -1,0 }); }
        else if (line[0] == 'D') { movements.push_back({ 1,0 }); }
        else if (line[0] == 'L') { movements.push_back({ 0,-1 }); }
        else if (line[0] == 'R') { movements.push_back({ 0, 1 }); }
        std::string repeat = line.substr(1);
        times.push_back(std::stoi(repeat));
    }
}

pairi Day9::sum(pairi& a, pairi& b) {
    return { a.first + b.first,a.second + b.second };
}
pairi Day9::diff(pairi& a, pairi& b) {
    return { a.first - b.first,a.second - b.second };
}
