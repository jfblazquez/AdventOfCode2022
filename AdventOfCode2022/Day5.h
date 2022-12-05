#pragma once
#include "BaseDay.h"
#include <vector>
#include <string>

struct Action {
    int amount{};
    int from{};
    int to{};
};

class Day5 :
    public BaseDay {
public:
    Day5();
    int puzzle1();
    int puzzle2();
private:

    /// parse stack and movements
    void fillData();
    void fillInitialStack(const std::string& str);
    void fillAction(const std::string& str);
    std::vector<Action> actions;
    std::vector<std::string> stacks;

};

