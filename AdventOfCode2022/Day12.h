#pragma once
#include <tuple>
#include <vector>
#include <array>
#include <string>
#include "BaseDay.h"

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;
// Creating a shortcut for tuple<double, int, int> type
typedef tuple<double, int, int> Tuple;

//#define TESTDAY12

#ifdef TESTDAY12
constexpr int ROWSIZE = 5;
constexpr int COLSIZE = 8;
#else
constexpr int ROWSIZE = 41;
constexpr int COLSIZE = 161;
#endif

class Day12 :
    public BaseDay {
public:
    Day12();
    int puzzle1();
    int puzzle2();
private:

    void fillData();

	vector<string> input{
	"Sabqponm",
	"abcryxxl",
	"accszExk",
	"acctuvwj",
	"abdefghi" };

	// Description of the Grid: signal value
	array<array<int, COLSIZE>, ROWSIZE> grid;

	Pair src{ -1, -1 };
	Pair dest{ -1, -1 };

};

