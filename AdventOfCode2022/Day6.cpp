#include <iostream>
#include <fstream>
#include<limits>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include <cassert>
#include <array>
#include <cctype>
#include "utils.h"

using namespace std;

#include "Day6.h"

Day6::Day6() {
	day = 6;
	filename = "input/day6.txt";
}

int Day6::findMarker() {
    fillData();
    size_t signalSize = signal.size();
    int result = -1;
    for (size_t i = 0; i < signalSize - markerSize; i++) {
        marker = signal.substr(i, markerSize);
        if (validMarker()) {
            result = i + markerSize;
            break;
        }
    }
    return result;
}

int Day6::puzzle1() {
    constexpr int puzzle1Marker = 4;
    markerSize = puzzle1Marker;
    return findMarker();
}

int Day6::puzzle2() {
    constexpr int puzzle2Marker = 14;
    markerSize = puzzle2Marker;
    return findMarker();
}

void Day6::fillData()
{

    ifstream ifs(filename, ios::binary);
    getline(ifs, signal);
    
    //test
    //signal = "mjqjpqmgbljsphdztnvjfqwrcgsmlb"; //7
    //signal = "bvwbjplbgvbhsrlpgdmjqwftvncz"; //5
    //signal = "nppdvjthqldpwncqszvftbrmjlhg"; //6
    //signal = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"; //10
    //signal = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"; //11
}

bool Day6::validMarker()
{
    if (marker.size() != markerSize) {
        return false;
    }

    vector<int> rep;
    rep.resize(127);
    for (char c : marker) {
        if (rep[c]) {
            return false;
        }
        rep[c]++;
    }
    return true;
}
