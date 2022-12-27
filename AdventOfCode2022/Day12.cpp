#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cctype>
#include "utils.h"

#include "Day12.h"

//From https://www.geeksforgeeks.org/a-search-algorithm/ 
// A C++ Program to implement A* Search Algorithm
#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
using namespace std;

int stepsPuzzle = 0;
// hold the necessary parameters
struct cell {
	// Row and Column index of its parent
	Pair parent;
	// f = g + h
	double f, g, h;
	cell() : parent(-1, -1), f(-1), g(-1), h(-1) {}
};

// check whether given cell (row, col) is a valid cell or not.
template <size_t ROW, size_t COL>
bool isValid(const array<array<int, COL>, ROW>& grid, const Pair& point) {
	// Returns true if row number and column number is in range
	if (ROW > 0 && COL > 0) {
		return (point.first >= 0) && (point.first < ROW)
			&& (point.second >= 0)
			&& (point.second < COL);
	}
	return false;
}

template <size_t ROW, size_t COL>
bool isValidFromTo(const array<array<int, COL>, ROW>& grid, const Pair& from, const Pair& to, bool inverse) {
	int valFrom = grid[from.first][from.second];
	int valTo = grid[to.first][to.second];
	if (!inverse) { return valFrom + 1 >= valTo; }
	return valFrom <= valTo || valFrom == valTo + 1;
}

// check whether the given cell is blocked or not
template <size_t ROW, size_t COL>
bool isUnBlocked(const array<array<int, COL>, ROW>& grid, const Pair& point) {
	// Returns true if the cell is not blocked else false
	return true;
	//return isValid(grid, point) && grid[point.first][point.second] == 1;
}

// check whether destination cell has been reached or not
bool isDestination(const Pair& position, const Pair& dest) {
	return position == dest;
}

// calculate the 'h' heuristics.
double calculateHValue(const Pair& src, const Pair& dest) {
	// h is estimated with the two points distance formula
	return sqrt(pow((src.first - dest.first), 2.0) + pow((src.second - dest.second), 2.0));
}

// trace the path from the source to destination
template <size_t ROW, size_t COL>
void tracePath(const array<array<cell, COL>, ROW>& cellDetails, const array<array<int, COL>, ROW>& grid, const Pair& dest) {	
	stack<Pair> Path;
	int row = dest.first;
	int col = dest.second;
	Pair next_node = cellDetails[row][col].parent;
	do {
		Path.push(next_node);
		next_node = cellDetails[row][col].parent;
		row = next_node.first;
		col = next_node.second;
	} while (cellDetails[row][col].parent != next_node);

	//printf("\nThe Path is (%zu steps) ", Path.size());
	stepsPuzzle = (int)Path.size();
	Path.emplace(row, col);
	while (!Path.empty()) {
		Pair p = Path.top();
		Path.pop();
		//printf("-> (%d,%d,%c) ", p.first, p.second, grid[p.first][p.second]);
	}
}

// A Function to find the shortest path between a given source cell to a destination cell according to A* Search Algorithm
template <size_t ROW, size_t COL>
void aStarSearch(const array<array<int, COL>, ROW>& grid, const Pair& src, const Pair& dest, bool inverse) {
	// If the source is out of range
	if (!isValid(grid, src)) {
		printf("Source is invalid\n");
		return;
	}

	// If the destination is out of range
	if (!isValid(grid, dest)) {
		printf("Destination is invalid\n");
		return;
	}

	// Either the source or the destination is blocked
	if (!isUnBlocked(grid, src) || !isUnBlocked(grid, dest)) {
		printf("Source or the destination is blocked\n");
		return;
	}

	// If the destination cell is the same as source cell
	if (isDestination(src, dest)) {
		printf("We are already at the destination\n");
		return;
	}

	// Create a closed list and initialise it to false which means that no cell has been included yet This closed
	// list is implemented as a boolean 2D array
	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	// Declare a 2D array of structure to hold the details of that cell
	array<array<cell, COL>, ROW> cellDetails;

	int i, j;
	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent = { i, j };

	/*
	Create an open list having information as-
	<f, <i, j>>
	where f = g + h,
	and i, j are the row and column index of that cell
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	This open list is implemented as a set of tuple.*/
	std::priority_queue<Tuple, std::vector<Tuple>, std::greater<Tuple>> openList;

	// Put the starting cell on the open list and set its 'f' as 0
	openList.emplace(0.0, i, j);

	// We set this boolean value as false as initially  the destination is not reached.
	while (!openList.empty()) {
		const Tuple& p = openList.top();
		// Add this vertex to the closed list
		i = get<1>(p); // second element of tuple
		j = get<2>(p); // third element of tuple
		Pair parent{ i, j };

		// Remove this vertex from the open list
		openList.pop();
		closedList[i][j] = true;
		//Generating all the 8 successor of this cell
		/*
				Cell-->Popped Cell (i, j)
				N --> North     (i-1, j)
				S --> South     (i+1, j)
				E --> East     (i, j+1)
				W --> West         (i, j-1)
				N.E--> North-East (i-1, j+1)
				N.W--> North-West (i-1, j-1)
				S.E--> South-East (i+1, j+1)
				S.W--> South-West (i+1, j-1)
		*/
		bool onlyOrthogonal = true;
		for (int add_x = -1; add_x <= 1; add_x++) {
			for (int add_y = -1; add_y <= 1; add_y++) {
				if (onlyOrthogonal) {
					if (add_x != 0 && add_y != 0) {
						//Do not add nodes NE NW SE or SW
						continue;
					}
				}

				Pair neighbour(i + add_x, j + add_y);
				// Only process this cell if this is a valid one
				if (isValid(grid, neighbour) && isValidFromTo(grid, parent, neighbour, inverse)) {
					// If the destination cell is the same as the current successor
					if (isDestination(neighbour, dest)) {
						// Set the Parent of the destination cell
						cellDetails[neighbour.first][neighbour.second].parent = { i, j };						
						tracePath(cellDetails, grid, dest);
						return;
					}
					// If the successor is already on the closed list or if it is blocked, then ignore it.
					else if (!closedList[neighbour.first][neighbour.second] && isUnBlocked(grid, neighbour)) {
						double gNew, hNew, fNew;
						gNew = cellDetails[i][j].g + 1.0;
						hNew = calculateHValue(neighbour, dest);
						fNew = gNew + hNew;

						// If it isn’t on the open list, add it to the open list. Make the current square the parent 
						// of this square. Record the f, g, and h costs of the square cell

						// If it is on the open list, check to see if this path to that square is better, using 'f' cost as the measure.
						if (cellDetails[neighbour.first][neighbour.second].f == -1 || cellDetails[neighbour.first][neighbour.second].f > fNew) {
							openList.emplace(fNew, neighbour.first, neighbour.second);

							// Update the details of this cell
							cellDetails[neighbour.first][neighbour.second].g = gNew;
							cellDetails[neighbour.first][neighbour.second].h = hNew;
							cellDetails[neighbour.first][neighbour.second].f = fNew;
							cellDetails[neighbour.first][neighbour.second].parent = { i, j };
						}
					}
				}
			}
		}
	}

	// When the destination cell is not found and the open list is empty, then we conclude that we failed to
	// reach the destination cell. This may happen when the there is no way to destination cell (due to blockages)
	//printf("Failed to find the Destination Cell\n");
}

Day12::Day12() {
	day = 12;
#ifdef TESTDAY12
	filename = "input/day12test.txt";
#else
	filename = "input/day12.txt";
#endif
}

int Day12::puzzle1() {
    fillData();
	aStarSearch(grid, src, dest, false);
	return stepsPuzzle;
}

int Day12::puzzle2() {
	int minStepsPuzzle = stepsPuzzle;
    fillData();

	//Brute Force Search (BFS) , next time implement the real BFS instead of A*
	for (int r = 0; r < ROWSIZE; r++) {
		for (int c = 0; c < COLSIZE; c++) {
			int value = input[r][c];
			if (value == 'a') {
				Pair newStart{ r,c };
				aStarSearch(grid, dest, newStart, true);
				if (stepsPuzzle < minStepsPuzzle) {
					minStepsPuzzle = stepsPuzzle;
				}
			}
		}
	}
	
    return minStepsPuzzle;
}

void Day12::fillData()
{

    std::ifstream ifs(filename, std::ios::binary);
    std::string line;

	input.clear();
	while (getline(ifs, line)) {
		input.push_back(line);
	}

	for (int r = 0; r < ROWSIZE; r++) {
		for (int c = 0; c < COLSIZE; c++) {
			int value = input[r][c];
			if (value == 'S') {
				src = { r,c };
				value = 'a';
			}
			else if (value == 'E') {
				dest = { r,c };
				value = 'z';
			}

			grid[r][c] = value;
		}
	}
}