#include <iostream>
#include <fstream>
#include<limits>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include <cassert>
#include <array>
#include <stdexcept>

using namespace std;

#include "Day3.h"

Day3::Day3() {
	day = 3;
	filename = "input/day3.txt";
}

int getVal(char c) {
    //Lowercase item types a through z have priorities 1 through 26.
    //Uppercase item types A through Z have priorities 27 through 52.
    if (c >= 'a' && c <= 'z') return c - 'a' + 1;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 27;
    throw std::logic_error("Not valid input value");
}

int Day3::puzzle1() {

    std::vector<int> occ;
    ifstream ifs(filename, ios::binary);
    std::string strstream;
    int result = 0;
    while (getline(ifs, strstream)) {
        occ.clear();
        occ.resize(127);
        size_t size = strstream.size();
        assert(size % 2 == 0);
        size_t halfStart = size / 2;
        //add
        for (size_t left = 0; left < halfStart; left++) {
            occ[strstream[left]]=1;
        }
        //locate right
        for (size_t right = halfStart; right < size; right++) {
            if (occ[strstream[right]]) {
                result += getVal(strstream[right]);
                break;
            }
        }
    }
    return result;
}

using tbool = std::array<bool, 3>;

int Day3::puzzle2() {
    std::vector<tbool> occ;
    ifstream ifs(filename, ios::binary);
    std::string strstream;
    int result = 0;
    int posGroup = 0; //%3
    occ.resize(127);
    while (getline(ifs, strstream)) {      
        size_t size = strstream.size();
        for (size_t elem = 0; elem < size; elem++) {
            occ[strstream[elem]][posGroup] = true;
        }

        posGroup = ++posGroup % 3;
        if (posGroup == 0) {
            for (char pos = 0; pos < 127; pos++) {
                if (occ[pos][0] && occ[pos][1] && occ[pos][2]) {
                    result += getVal(pos);
                    break;
                }
            }
            occ.clear();
            occ.resize(127);
        }
    }
    return result;
}