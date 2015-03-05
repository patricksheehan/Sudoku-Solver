// Patrick Sheehan

#ifndef PUZZLE_H
	#define PUZZLE_H

#include <set>
using namespace std;

class Puzzle;

class Cell {
    friend class Puzzle;
    bool solved;    // used to quickly check if the cell has been solved
    set<char> possibleValues; // set that will contain all the possible values
        
    Cell operator= (const Cell &); // equality operator for a cell
    bool findValue(const char); // checks for a value
public:
    Cell(){solved = false;} // default constructor
}; // Cell

class Puzzle {
    Cell board [9][9]; // this will be a 2-D array of cells, 81 in total
    void removeImpossibilities();
public:
    Puzzle(){} // need default constructor
    Puzzle(char const *); // constructor based on input string
    bool solved(); // returns true if the puzzle has been solved
    void printSolution();// prints out a solved puzzle cell by cell      
    bool decideSingles(); // finds and decides all apparent singles
    bool hiddenSingles(); // searches for hidden singles and simplifies
    bool guess(Puzzle &); // last resort, checks for impossibilities and guesses
    Puzzle operator= (const Puzzle &); // equality operator for Puzzles
};

#endif
