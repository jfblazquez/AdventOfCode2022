#pragma once
#include "BaseDay.h"

class Day :
    public BaseDay {
public:
    Day();
    int puzzle1();
    int puzzle2();
private:

    void fillData();

};

