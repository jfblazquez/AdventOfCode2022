#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include "utils.h"

#include "Day10.h"

Day10::Day10() {
	day = 10;
	filename = "input/day10.txt";
}



int Day10::puzzle1() {
    fillData();
    CycleValue prevCycle{ 0, 0 };
    
    int cycle = 20;
    long long signal = 0;
    const int sumCycle = 40;
    for (auto& currentCycle : status) {
        if (currentCycle.first >= cycle) {
            if (currentCycle.first == cycle) {
                signal += currentCycle.second * cycle;
            }
            else
            {
                signal += prevCycle.second * cycle;
            }
            cycle += sumCycle;
        }
        prevCycle = currentCycle;
    }
    return signal;
}

int Day10::puzzle2() {
    if (status.empty()) {
        fillData();
    }
    fillData();

    int cycle = 1;
    int pixel = 0;
    long long signal = 0;
    int statusPos = -1;
    int x = 1;
    for (int cycle = 1; cycle <= 240; cycle++) {
        if (status[statusPos + 1].first == cycle) {
            x = status[statusPos + 1].second;
            statusPos++;
        }

        if (pixel + 1 == x || pixel - 1 == x || pixel == x) {
            std::cout << "#";
        }
        else {
            std::cout << ".";
        }

        pixel++;
        if (pixel % 40 == 0) {
            pixel = 0;
            std::cout << "\n";
        }
    }
    return std::numeric_limits<int>::max();
}

void Day10::fillData()
{
    std::ifstream ifs(filename, std::ios::binary);
    std::string line;
    int cycle = 1;
    int x = 1;
    while (getline(ifs, line)) {

        if (line[0] == 'n') //noop
        {
            cycle++;
        }
        else
        {
            cycle += 2;
            int sumx = std::stoi(line.substr(5));
            x += sumx;
            status.push_back({ cycle , x });
        }
    }
}
