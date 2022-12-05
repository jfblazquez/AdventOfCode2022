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

#include "Day5.h"

Day5::Day5() {
	day = 5;
	filename = "input/day5.txt";
}

int Day5::puzzle1() {
    fillData();
    for (auto& action : actions) {
        for (int i = 0; i < action.amount; i++) {
            char elem = stacks[action.from].back();
            stacks[action.from].pop_back();
            stacks[action.to].push_back(elem);
        }
    }

    std::string s;
    for (auto& stack : stacks) {
        s.push_back(stack.back());
    }
    cout << "Day " << getDay() << " puzzle 1: " << s << "\n";
    int result = std::numeric_limits<int>::max();
    return result;
}

int Day5::puzzle2() {
    fillData();
    for (auto& action : actions) {
        std::string& sFrom = stacks[action.from];
        std::string& sTo = stacks[action.to];
        sTo += sFrom.substr(sFrom.size() - action.amount, action.amount);
        sFrom.erase(sFrom.size() - action.amount);
    }

    std::string s;
    for (auto& stack : stacks) {
        s.push_back(stack.back());
    }
    cout << "Day " << getDay() << " puzzle 2: " << s << "\n";
    int result = std::numeric_limits<int>::max();
    return result;
}

void Day5::fillData()
{
    stacks.clear();
    actions.clear();
    ifstream ifs(filename, ios::binary);
    std::string strstream;
    bool readingInitialStack = true;
    while (getline(ifs, strstream)) {
        if (readingInitialStack) {
            if (strstream.empty()) {
                readingInitialStack = false;
            }
            else {
                fillInitialStack(strstream);
            }
        }
        else
        {
            //Read actions. As index start in 0, will sustract 1 in "from" and "to"
            fillAction(strstream);
        }
    }

}

void Day5::fillInitialStack(const std::string& str)
{
    //Line structure
    //[0].[1].[2].....[3] . for space
    //0123456789012345678.
    //Data starts at 1 and every 4 chars new col. if space ignore
    size_t size = str.size();
    size_t pos = 1;
    size_t stack = 0;
    while (pos < size) {
        if (stacks.size() <= stack) {
            stacks.resize(stack + 1);
        }
        char strpos = str[pos];
        if (strpos != ' ' && std::isalpha(strpos)) {
            stacks[stack].insert(stacks[stack].begin(),strpos); //push_front
        }
        pos += 4;
        stack++;
    }
}

void Day5::fillAction(const std::string& str)
{
    auto splitstr = utils::string::split(str, ' ');
    constexpr int actionIndex = 1;
    constexpr int fromIndex = 3;
    constexpr int toIndex = 5;
    int action = std::stoi(splitstr[actionIndex]);
    int from = std::stoi(splitstr[fromIndex]) - 1;
    int to = std::stoi(splitstr[toIndex]) -1 ;
    actions.push_back({ action, from, to });
}