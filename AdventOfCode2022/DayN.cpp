#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include "utils.h"

#include "Day.h"

Day::Day() {
	day = ;
	filename = "input/day.txt";
}



int Day::puzzle1() {
    fillData();
    return 0;
}

int Day::puzzle2() {
    //fillData();
    return 0;
}

void Day::fillData()
{
    std::ifstream ifs(filename, std::ios::binary);
    std::string line;
    while (getline(ifs, line)) {

    }

}
