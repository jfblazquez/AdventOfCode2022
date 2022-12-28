#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include "utils.h"

#include "Day13.h"

constexpr int STARTLISTTOKEN = -1;
constexpr int ENDLISTTOKEN = -2;

Day13::Day13() {
	day = 13;
	filename = "input/day13.txt";
}

int Day13::puzzle1() {
    //4784 is too low
    //6242 is too high
    //new val 6240 but want to revise code
    //added a vs [a,b,c] and [a,b,c] vs a but did not change result, no cases

    fillData();
    int result = 0;
    for (auto i = 0; i < elements.size() / 2; i++) {
        auto& left = elements[i * 2];
        auto& right = elements[(i * 2)+1];
        int pair = i + 1;
        bool go = goodOrder(left, right);
        std::cout << "Pair: " << pair << " goodOrder: " << std::boolalpha << go << "\n";
        if (go) {
            result += pair;
        }
    }
    return result;
}

int Day13::puzzle2() {
    if (elements.empty()) { fillData(); }
    elements.push_back(levelValuesFromString("[[2]]"));
    elements.push_back(levelValuesFromString("[[6]]"));
    auto sorter = [](const levelValues& left, const levelValues& right) -> bool {
        return goodOrder(left, right);
    };
    std::sort(elements.begin(), elements.end(), sorter);
    int dividerPacket2Indx = 0;
    int dividerPacket6Indx = 0;
    for (auto i = 0; i < elements.size(); i++) {
        int index = i + 1;
        levelValues& elem = elements[i];
        if (elem.size() == 5 &&
            elem[0].second == STARTLISTTOKEN &&
            elem[1].second == STARTLISTTOKEN &&
            elem[3].second == ENDLISTTOKEN &&
            elem[4].second == ENDLISTTOKEN)
        {
            if (elem[2].second == 2) {
                dividerPacket2Indx = index;
            }
            else if (elem[2].second == 6) {
                dividerPacket6Indx = index;
            }
        }
    }
    return dividerPacket2Indx * dividerPacket6Indx;
}

void Day13::fillData()
{
    std::ifstream ifs(filename, std::ios::binary);
    std::string line;
    while (getline(ifs, line)) {
        levelValues lv = levelValuesFromString(line);
        if (!lv.empty()) {
            elements.push_back(std::move(lv));
        }
    }

}

levelValues levelValuesFromString(const std::string& line) {
    levelValues lv;
    int level = 0;
    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '[') {
            level++;
            lv.push_back({ level,STARTLISTTOKEN }); //List created
        }
        else if (c == ']') {
            lv.push_back({ level,ENDLISTTOKEN }); //List created
            level--;
        }
        else if (c == ',') {
            //pass to next number
        }
        else {
            std::string snumber{ c };
            while (i + 1 < line.size() && std::isdigit(line[i + 1])) {
                i++;
                snumber.push_back(line[i]);
            }
            int value = std::stoi(snumber);
            lv.push_back({ level,value });
        }
    }
    return lv;

}

bool goodOrder(const levelValues& left, const levelValues& right) {
    auto lit = left.begin();
    auto rit = right.begin();

    bool goodOrder = true;
    while (lit != left.end() && rit != right.end()) {
        if (lit->second == STARTLISTTOKEN && rit->second == ENDLISTTOKEN) {
            //right go up before left, run out of elements
            goodOrder = false;
            break;
        }
        else if (lit->second == ENDLISTTOKEN && rit->second == STARTLISTTOKEN) {
            ///Left side ran out of items 
            goodOrder = true;
            break;
        }
        else if (lit->second == STARTLISTTOKEN && rit->second == STARTLISTTOKEN) {
            // all good
        }
        else if (lit->second == STARTLISTTOKEN) {
            // left list, right int
            // [a,b,c] vs [d]
            // maybe [] vs [d] which is good
            // a should be less, if a == d, right will run out of elements so bad order                
            while (lit->second == STARTLISTTOKEN) { lit++; }
            if (lit->second < rit->second) { //here is included ENDLISTTOKEN as it is < 0
                //great, move lit to ENDLISTTOKEN
                //TODO for part2?: MOVE TO THE SAME LEVEL??? MAYBE NESTED LIST NEED TO BE IGNORED?
                //while (lit->second != ENDLISTTOKEN) { lit++; }
                 //goodOrder = true;
                break;
            }
            else if (lit->second > rit->second) {
                goodOrder = false;
                break;
            }
            //what if [a,b,c] vs [a] --> bad because right run out of elements
            else if (lit->second == rit->second && (lit + 1)->second != ENDLISTTOKEN) {
                goodOrder = false;
                break;
            }
        }
        else if (rit->second == STARTLISTTOKEN) {
            // left int, right list
            // [a] vs [b,c,d]
            // maybe [a] vs [] which is bad as right run out of elements
            // maybe [a] vs [[b]] so find first element to compare
            while (rit->second == STARTLISTTOKEN) { rit++; }
            if (rit->second == ENDLISTTOKEN) {
                goodOrder = false;
                break;
            }

            if (lit->second < rit->second) {
                //great, move rit to ENDLISTTOKEN
                //TODO for part2: MOVE TO THE SAME LEVEL??? MAYBE NESTED LIST NEED TO BE IGNORED?
                //while (rit->second != ENDLISTTOKEN) { rit++; }
                 //goodOrder = true;
                break;
            }
            else if (lit->second > rit->second) {
                goodOrder = false;
                break;
            }
            //what if [a] vs [a,b,c] vs --> good because left run out of elements
            else if (lit->second == rit->second && (rit + 1)->second != ENDLISTTOKEN) {
                goodOrder = true;
                break;
            }
        }
        else if (lit->second > rit->second) {
            goodOrder = false;
            break;
        }
        else if (lit->second < rit->second) {
            //goodOrder = true;
            break;
        }
        lit++;
        rit++;
    }
    return goodOrder;
}