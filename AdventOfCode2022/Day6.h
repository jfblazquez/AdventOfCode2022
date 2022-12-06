#pragma once
#include "BaseDay.h"
#include <array>
#include <string>

class Day6 :
    public BaseDay {
public:
    Day6();
    int puzzle1();
    int puzzle2();
private:

    /// parse stack and movements
    void fillData();
    std::string signal;
    size_t markerSize = 4; //4 and 14
    std::string marker;
    
    /// Verify if marker has markerSize and all unique chars
    bool validMarker();

    /// Encapsulate puzzle1 as puzzle2 is very similar
    int findMarker();
};

