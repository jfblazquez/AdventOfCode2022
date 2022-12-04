#pragma once
#include "BaseDay.h"

class Day4 :
    public BaseDay {
public:
    Day4();
    int puzzle1();
    int puzzle2();
private:

    /// parse a-b,c-d
    void strtoabcd(const std::string& strstream);
    int a{};
    int b{};
    int c{};
    int d{};
};

