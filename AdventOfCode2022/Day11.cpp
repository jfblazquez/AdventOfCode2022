#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include "utils.h"

#include "Day11.h"

Day11::Day11() {
	day = 11;
	filename = "input/day11.txt";
}

int Day11::puzzle1() {
    fillData();
    constexpr int roundsP1 = 20;
    constexpr int reliefP1 = 3;
    int dimensionP1 = 1;
    for (auto& m : monkeys) {
        dimensionP1 *= m.divisibleBy;
    }
    return doRounds(roundsP1, reliefP1, dimensionP1);
}

int Day11::puzzle2() {
    fillData();
    constexpr int roundsP2 = 10000;
    constexpr int reliefP2 = 1;
    int dimensionP2 = 1;
    for (auto& m : monkeys) {
        dimensionP2 *= m.divisibleBy;
    }
    long long result = doRounds(roundsP2, reliefP2, dimensionP2);

    std::cout << "Day 11 puzzle 2: " << result;
    return std::numeric_limits<int>::max();
}

void Day11::fillData()
{
    monkeys.clear();
    std::ifstream ifs(filename, std::ios::binary);
    std::string line;

    while (getline(ifs, line)) {
        if (line[0] != 'M') {
            continue;
        }
        Monkey m;
        //items
        getline(ifs, line);
        auto items = utils::string::split(line.substr(18),',');
        for (auto& it : items) {
            m.items.push_back(std::stoi(it));
        }
        //operation
        getline(ifs, line);
        Operation op{};
        int val{};
        if (line.substr(23) == "* old") {
            op = Operation::square;            
        }
        else {
            char opc = line[23];
            val = std::stoi(line.substr(25));
            if (opc == '+') {
                op = Operation::sum;
            }
            else if (opc == '*') {
                op = Operation::mult;
            }
        }

        m.op = op;
        m.opVal = val;

        //divisible by
        getline(ifs, line);
        m.divisibleBy = std::stoi(line.substr(21));

        //true throw
        getline(ifs, line);
        m.throwTrue = std::stoi(line.substr(29));

        //false throw
        getline(ifs, line);
        m.throwFalse = std::stoi(line.substr(30));

        monkeys.emplace_back(std::move(m));
    }

}

long long Day11::doRounds(int rounds, int relief, int dimension)
{
    std::vector<int> inspections;
    inspections.resize(monkeys.size());
    for (int r = 0; r < rounds; r++) {
        for (auto& m : monkeys) {
            int elems = m.items.size();
            m.inspections += elems;
            for (int i = 0; i < elems; i++) {
                long long  itemWorry = m.items[i];
                if (m.op == Operation::sum) {
                    itemWorry += m.opVal;
                }
                else if (m.op == Operation::mult) {
                    itemWorry *= m.opVal;
                }
                else if (m.op == Operation::square) {
                    itemWorry *= itemWorry;
                }
                itemWorry = itemWorry / relief;
                itemWorry = itemWorry % dimension;
                if (itemWorry % m.divisibleBy == 0) {
                    monkeys[m.throwTrue].items.push_back(itemWorry);
                }
                else {
                    monkeys[m.throwFalse].items.push_back(itemWorry);
                }
            }
            m.items.clear();
        }
    }

    std::sort(monkeys.begin(), monkeys.end(), [&](Monkey& a, Monkey& b) { return a.inspections > b.inspections; });
    long long result = monkeys[0].inspections * monkeys[1].inspections;
    return result;
}
