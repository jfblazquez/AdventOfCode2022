#pragma once
#include "BaseDay.h"
#include <vector>

enum class Operation { sum, mult, square };

struct Monkey {
    std::vector<long long> items{};
    Operation op{Operation::sum};
    int opVal{};
    int divisibleBy{};
    int throwTrue{};
    int throwFalse{};

    long long inspections{};
};

using Monkeys = std::vector<Monkey>;

class Day11 :
    public BaseDay {
public:
    Day11();
    int puzzle1();
    int puzzle2();
private:

    void fillData();
    long long doRounds(int rounds, int relief, int dimension);
    Monkeys monkeys;
};

