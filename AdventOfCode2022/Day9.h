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
    pairi sum(pairi& a, pairi& b);
    pairi diff(pairi& a, pairi& b);

    std::vector<pairi> movements;
    std::vector<int> times;
    std::set<pairi> visited;
};

