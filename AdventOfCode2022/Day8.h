#pragma once
#include<memory>
#include <map>
#include <string>
#include "BaseDay.h"

class Day8 :
    public BaseDay {
public:
    Day8();
    int puzzle1();
    int puzzle2();
private:

    /// parse matrix and fill row and col
    void fillData();

    bool isVisible(int row, int col);
    bool isVisibleTop(int r, int c);
    bool isVisibleBottom(int r, int c);
    bool isVisibleRight(int r, int c);
    bool isVisibleLeft(int r, int c);

    int scenicScore(int r, int c);
    int scenicScoreTop(int r, int c);
    int scenicScoreBottom(int r, int c);
    int scenicScoreRight(int r, int c);
    int scenicScoreLeft(int r, int c);

    int sizeRow{};
    int sizeCol{};
    std::vector<std::vector<int>> m;

};

