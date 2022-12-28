#pragma once
#include "BaseDay.h"
#include <memory>

using levelValue = std::pair<int, int>;
using levelValues = std::vector<levelValue>;

levelValues levelValuesFromString(const std::string& line);
bool goodOrder(const levelValues& left, const levelValues& right);

class Day13 :
    public BaseDay {
public:
    Day13();
    int puzzle1();
    int puzzle2();
private:

    void fillData();


    std::vector<levelValues> elements;
};
