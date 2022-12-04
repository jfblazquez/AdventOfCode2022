#include <iostream>
#include <fstream>
#include<limits>
#include<vector>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

#include "Day2.h"

Day2::Day2() {
	day = 2;
	filename = "input/day2.txt";
}

int Day2::puzzle1() {

    std::map<std::string, int> r;
    r["A X"] = 1+3; // draw rock-rock
    r["A Y"] = 2+6; // win rock-paper
    r["A Z"] = 3+0; // lose rock-scissors

    r["B X"] = 1+0; // lose paper-rock
    r["B Y"] = 2+3; // draw 
    r["B Z"] = 3+6; // win pape-scisoors

    r["C X"] = 1+6; // win scissors-rock
    r["C Y"] = 2+0; // lose scissors-paper
    r["C Z"] = 3+3; // draw

    //points = shape (1X 2Y 3Z) + result(0 lost, 3 draw, 6 win)

    //AX for Rock, BY for Paper, and CZ for Scissors
    //abc oponnent
    //xyz your choice
    //Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock. 
    

    ifstream ifs(filename, ios::binary);
    int result = 0;
    std::string strstream;
    while (getline(ifs, strstream)) {
        result += r[strstream];        
    }

    return result;
}

int Day2::puzzle2() {

    std::map<std::string, int> r;
    r["A X"] = 0 + 3; // lose rock-scissors
    r["A Y"] = 3 + 1; // draw rock-rock
    r["A Z"] = 6 + 2; // win rock-paper

    r["B X"] = 0 + 1; // lose paper-rock
    r["B Y"] = 3 + 2; // draw paper-paper
    r["B Z"] = 6 + 3; // win paper-scissors

    r["C X"] = 0 + 2; // lose scissors-paper
    r["C Y"] = 3 + 3; // draw scissors-scissors
    r["C Z"] = 6 + 1; // win scissors-rock

    //points = shape (1rock 2paper 3scissors) + result(0 lost, 3 draw, 6 win)

    //AX for Rock, BY for Paper, and CZ for Scissors
    //abc oponnent
    //not anymore: xyz your choice
    // X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win.
    //Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock. 


    ifstream ifs(filename, ios::binary);
    int result = 0;
    std::string strstream;
    while (getline(ifs, strstream)) {
        result += r[strstream];
    }

    return result;
}