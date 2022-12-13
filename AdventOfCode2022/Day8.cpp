#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include "utils.h"

using namespace std;

#include "Day8.h"

Day8::Day8() {
	day = 8;
	filename = "input/day8.txt";
}



int Day8::puzzle1() {
    fillData();
    int visible = 2*sizeRow + 2*sizeCol - 4;
    for (int row = 1; row < sizeRow - 1; row++) {
        for (int col = 1; col < sizeCol - 1; col++) {
            visible += isVisible(row, col);
        }
    }

    return visible;
}

int Day8::puzzle2() {
    m.clear();
    fillData();
    int maxScenicScore = 0;
    for (int row = 1; row < sizeRow - 1; row++) {
        for (int col = 1; col < sizeCol - 1; col++) {
            int score = scenicScore(row, col);
            if (score > maxScenicScore) {
                maxScenicScore = score;
            }
        }
    }
    return maxScenicScore;
}

void Day8::fillData()
{
    std::ifstream ifs(filename, std::ios::binary);
    std::string line;
    while (getline(ifs, line)) {
        std::vector<int> rowV;
        for (char c : line) {
            rowV.push_back(c - '0');
        }
        m.push_back(rowV);
    }
    sizeCol = m.back().size();
    sizeRow = m.size();
}

bool Day8::isVisible(int row, int col) {
    return isVisibleTop(row, col) || isVisibleBottom(row, col) ||
        isVisibleLeft(row, col) || isVisibleRight(row, col);
}

bool Day8::isVisibleTop(int r, int c) {
    int h = m[r][c];
    for (int row = 0; row < r; row++) {
        if (m[r][c] <= m[row][c]) { return false; }
    }
    return true;
}

bool Day8::isVisibleBottom(int r, int c) {
    int h = m[r][c];
    for (int row = r + 1; row < sizeRow; row++) {
        if (m[r][c] <= m[row][c]) { return false; }
    }
    return true;
}

bool Day8::isVisibleLeft(int r, int c) {
    int h = m[r][c];
    for (int col = 0; col < c; col++) {
        if (m[r][c] <= m[r][col]) { return false; }
    }
    return true;
}

bool Day8::isVisibleRight(int r, int c) {
    int h = m[r][c];
    for (int col = c + 1; col < sizeCol; col++) {
        if (m[r][c] <= m[r][col]) { return false; }
    }
    return true;
}

int Day8::scenicScore(int r, int c) {
    return scenicScoreTop(r, c) * scenicScoreBottom(r, c)
        * scenicScoreRight(r, c) * scenicScoreLeft(r, c);
}
int Day8::scenicScoreTop(int r, int c) {
    int h = m[r][c];
    int score = 0;
    for (int row = r - 1; row >= 0; row--) {
        score++;
        if (m[r][c] <= m[row][c]) { break; }
    }
    return score;
}
int Day8::scenicScoreBottom(int r, int c) {
    int h = m[r][c];
    int score = 0;
    for (int row = r + 1; row < sizeRow; row++) {
        score++;
        if (m[r][c] <= m[row][c]) { break; }        
    }
    return score;
}
int Day8::scenicScoreRight(int r, int c) {
    int h = m[r][c];
    int score = 0;
    for (int col = c - 1; col >= 0; col--) {
        score++;
        if (m[r][c] <= m[r][col]) { break; }
    }
    return score;
}

int Day8::scenicScoreLeft(int r, int c) {
    int h = m[r][c];
    int score = 0;
    for (int col = c + 1; col < sizeCol; col++) {
        score++;
        if (m[r][c] <= m[r][col]) { break; }
    }
    return score;
}