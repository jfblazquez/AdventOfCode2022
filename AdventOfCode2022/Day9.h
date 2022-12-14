#pragma once
#include <set>
#include "BaseDay.h"

using pairi = std::pair<int, int>;

class Day9 :
    public BaseDay {
public:
    Day9();
    int puzzle1();
    int puzzle2();
private:

    void fillData();
    pairi sum(const pairi& a, const pairi& b);
    pairi diff(const pairi& a, const pairi& b);

    std::vector<pairi> movements;
    std::vector<int> times;
    std::set<pairi> visited;

    const pairi moveDown{ 1,0 };
    const pairi moveUp{ -1,0 };
    const pairi moveRight{ 0,1 };
    const pairi moveLeft{ 0,-1 };
};

