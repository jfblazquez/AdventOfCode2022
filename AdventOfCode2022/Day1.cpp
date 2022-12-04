#include <iostream>
#include <fstream>
#include<limits>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

#include "Day1.h"

Day1::Day1() {
	day = 1;
	filename = "input/day1.txt";
}

int Day1::puzzle1() {
    ifstream ifs(filename, ios::binary);
    int currentElf = 0;
    int maxElfCalories = 0;
    std::string strstream;
    while (getline(ifs, strstream)) {
        bool newElf = strstream.empty();
        if (newElf) {
            if (currentElf > maxElfCalories) {
                maxElfCalories = currentElf;                
            }
            currentElf = 0;
        }
        else {
            currentElf += std::stoi(strstream);
        }
    }
    int result = maxElfCalories;

    return result;
}

int Day1::puzzle2() {
    std::vector<int> allElfs;
    ifstream ifs(filename, ios::binary);
    int currentElf = 0;
    int maxElfCalories = 0;
    std::string strstream;
    while (getline(ifs, strstream)) {
        bool newElf = strstream.empty();
        if (newElf) {
            allElfs.push_back(currentElf);
            currentElf = 0;
        }
        else {
            currentElf += std::stoi(strstream);
        }
    }
    std::sort(allElfs.begin(), allElfs.end(), std::greater<>());
    
    int result = 0;
    for (size_t i = 0; i < std::min((size_t)3, allElfs.size()); i++) {
        result += allElfs[i];
    }

    return result;
}