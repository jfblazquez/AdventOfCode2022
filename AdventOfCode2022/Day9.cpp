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

    visited.insert(tail);
    for (int i = 0; i < movements.size(); i++) {
        auto& current = movements[i];
        for (int j = 0; j < times[i]; j++) {
            head = sum(head, current);
            auto htdiff = diff(head, tail);
            if (std::abs(htdiff.first) > 1 || std::abs(htdiff.second) > 1) {
                if (htdiff.first < 0) {
                    tail = sum(tail, moveUp);
                }
                else if (htdiff.first > 0) {
                    tail = sum(tail, moveDown);
                }
                if (htdiff.second < 0) {
                    tail = sum(tail, moveLeft);
                }
                else if (htdiff.second > 0) {
                    tail = sum(tail, moveRight);
                }
            }
            visited.insert(tail);
        }
    }
    return visited.size();
}

int Day9::puzzle2() {
    visited.clear();
    if (movements.empty()) {
        fillData();
    }

    int knots = 10;
    std::vector<pairi> rope;
    rope.resize(knots);
    visited.insert(rope[knots-1]);
    for (int i = 0; i < movements.size(); i++) {
        auto& current = movements[i];
        for (int j = 0; j < times[i]; j++) {
            for (int k = 1; k < knots ; k++) {
                pairi head = rope[k-1];
                pairi tail = rope[k];
                if (k == 1) {
                    head = sum(head, current);
                    rope[k - 1] = head;
                }
                auto htdiff = diff(head, tail);
                if (std::abs(htdiff.first) > 1 || std::abs(htdiff.second) > 1) {
                    if (htdiff.first < 0) {
                        tail = sum(tail, moveUp);
                    }
                    else if (htdiff.first > 0) {
                        tail = sum(tail, moveDown);
                    }
                    if (htdiff.second < 0) {
                        tail = sum(tail, moveLeft);
                    }
                    else if (htdiff.second > 0) {
                        tail = sum(tail, moveRight);
                    }                
                    rope[k] = tail;
                }
                else {
                    //No more movement in the rope go on
                    break;
                }

                if (k == knots - 1) {
                    visited.insert(tail);
                }
            }
        }
    }
    return visited.size();
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

pairi Day9::sum(const pairi& a, const pairi& b) {
    return { a.first + b.first,a.second + b.second };
}
pairi Day9::diff(const pairi& a, const pairi& b) {
    return { a.first - b.first,a.second - b.second };
}
