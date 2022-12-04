#include <iostream>
#include <fstream>
#include<limits>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include <cassert>
#include <array>

using namespace std;

#include "Day4.h"

Day4::Day4() {
	day = 4;
	filename = "input/day4.txt";
}

int Day4::puzzle1() {
    ifstream ifs(filename, ios::binary);
    std::string strstream;
    int result = 0;
    while (getline(ifs, strstream)) {
        strtoabcd(strstream);
        if (a >= c && b <= d) { result++; }
        else if (c >= a && d <= b) { result++; }
    }
    return result;
}

int Day4::puzzle2() {
    ifstream ifs(filename, ios::binary);
    std::string strstream;
    int result = 0;
    while (getline(ifs, strstream)) {
        strtoabcd(strstream);
        if (d >= a && c <= b) { result++; }
        else if (a >= d && b <= c) { result++; }
    }
    return result;
}

void Day4::strtoabcd(const std::string& strstream)
{
    size_t tokenpos = strstream.find('-', 0);
    a = std::stoi(strstream.substr(0, tokenpos));
    size_t startNext = tokenpos + 1;
    tokenpos = strstream.find(',', tokenpos + 1);
    b = std::stoi(strstream.substr(startNext, tokenpos - startNext));
    startNext = tokenpos + 1;
    tokenpos = strstream.find('-', tokenpos + 1);
    c = std::stoi(strstream.substr(startNext, tokenpos - startNext));
    startNext = tokenpos + 1;
    d = std::stoi(strstream.substr(startNext, strstream.size() - startNext));
    assert(a <= b);
    assert(c <= d);
}
