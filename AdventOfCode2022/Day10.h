#pragma once
#include "BaseDay.h"

using CycleValue = std::pair<int, int>;
using Status = std::vector<CycleValue>;

class Day10 :
    public BaseDay {
public:
    Day10();
    int puzzle1();
    int puzzle2();
private:

    void fillData();
    Status status;
};

