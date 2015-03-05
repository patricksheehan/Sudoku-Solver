// Patrick Sheehan
#include "puzzle.h"
#include <iostream>
using namespace std;

Puzzle::Puzzle(char const * input) {
    char values [] = {'1','2','3','4','5','6','7','8','9'}; // to initialize
    set<char> all_values(values, values + 9); // stores all possibilities

    for (int i = 0, j = 0; i < 81; j++) { // loop through all input and fill cell
        for (int k = 0; k < 9; k++) {
            if (input[i] == '.') {
                board[j][k].possibleValues = all_values; // cant make any decision
                board[j][k].solved = false; // unsolved
            }// if blank cell in input puzzle
            else { // else insert value and set solved
                board[j][k].possibleValues.insert(input[i]); // know this cell done
                board[j][k].solved = true; // set solved flag
            } // else
            i++; // iterate i
        } // for all columns
    } // for all rows

} // Constructor for Puzzle

/*
 * Without exception, removeImpossibilites removes the value of a solved cell
 * from other cells in the same row, column, and 3x3 square
 */
void Puzzle::removeImpossibilities() {
    char valueToRemove;
    /* 
     * iterate over the board where i = rows, j = columns
     * this for-loop finds solved cells, pulls the value of that solved cell
     * then removes that value as a possibility for the other cells in the same
     * row, column, and square    
     */
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j].solved) { // if a cell is solved
                valueToRemove = *(board[i][j].possibleValues.begin());
                for (int k = 0; k < 9; k++) { // remove in same row/column
                    if (k != j) // if not at solved cell
                        board[i][k].possibleValues.erase(valueToRemove);
                    if (k != i) // if not at solved cell
                        board[k][j].possibleValues.erase(valueToRemove);
                } // for all cells in solved cell's row/column
                // next iterate over the sub-block of the solved cell
                for (int r = (i - i % 3); r < (i - i % 3 + 3); r++) {
                    for (int c = (j - j % 3); c < (j - j % 3 + 3); c++) {
                        if (!(r == i || c == j)) // if not at solved cell
                            board[r][c].possibleValues.erase(valueToRemove);
                    } // for all cells in solved cell's square (column)  
                } // for all cells in solved cell's square (row)
            } // if cell solved
        }// for all columns
    } // for all rows 
} // removeImpossibilites ()


/*
 * decideSingles() calls removeImpossibilities() then checks for cells with only
 * one possibility, then decides on those cells.
 */
bool Puzzle::decideSingles() {
    removeImpossibilities(); // used already solved cells to limit possibilities
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if ((board[i][j].possibleValues.size() == 1) && !(board[i][j].solved)) { // if only one possibility
                return board[i][j].solved = true;
            } // if single found, set to solved
        } // for all columns
    } // for all rows
    return false;
} // decideSingles()


bool Puzzle:: hiddenSingles(){
    char values [] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    bool seenOnlyOnce [9];
    Cell * hiddenSingle;
    
    /* 
     * iterate over the board where i = rows, j = columns
     * this for-loop finds hidden singles and remove the other possibilities
     * from that cell.    
     */
    
    // iterate through the rows and check for values that only appear once
    for (int i = 0; i < 9; i++) { // for each row
        for (int n = 0; n < 9; n++) { // for each possible value
            
            seenOnlyOnce[n] = false; // initialize our "seen" array to once
            
            for (int j = 0; j < 9; j++) { // for each cell
                
                if (board[i][j].solved) { // if decided cell, dont care
                    if (board[i][j].findValue(values[n])) {
                        seenOnlyOnce[n] = false;
                        break; // if this row already has that value decided
                    } 
                    else
                        continue; // otherwise next cell
                } // if decided cell
                
                // Else, if we see the value
                if (board[i][j].findValue(values[n])) {
                    if(seenOnlyOnce[n]){ // if we've already seen it
                        seenOnlyOnce[n] = false; // no longer true
                        break; // skip to next row
                    } // if already seen
                    else{ // otherwise, first time seeing the value
                        seenOnlyOnce[n] = true;
                        hiddenSingle = &board[i][j];
                    } // else
                } // if see value    
            } // for each cell
            
            if(seenOnlyOnce[n]){ // if saw the value only once
                hiddenSingle->possibleValues.clear(); // empty that cell
                hiddenSingle->possibleValues.insert(values[n]); // insert single
                hiddenSingle->solved = true; // decide cell
                return true; // found a simplification
            } // if saw value only once
        } // for all values
    } // for all rows
    
    // iterate through the columns and check for values that only appear once
    for (int j = 0; j < 9; j++) { // for each column
        for (int n = 0; n < 9; n++) { // for each possible value
            
            seenOnlyOnce[n] = false; // initialize our "seen" array to once
            
            for (int i = 0; i < 9; i++) { // for each cell
                
                if (board[i][j].solved) { // if decided cell, dont care
                    if (board[i][j].findValue(values[n])) {
                        seenOnlyOnce[n] = false;
                        break; // if this row already has that value decided
                    } 
                    else
                        continue; // otherwise next cell
                } // if decided cell
                
                // Else, if we see the value
                if (board[i][j].findValue(values[n])) {
                    if(seenOnlyOnce[n]){ // if we've already seen it
                        seenOnlyOnce[n] = false; // no longer true
                        break; // skip to next row
                    } // if already seen
                    else{ // otherwise, first time seeing the value
                        seenOnlyOnce[n] = true;
                        hiddenSingle = &board[i][j];
                    } // else
                } // if see value    
            } // for each cell
            
            if(seenOnlyOnce[n]){ // if saw the value only once
                hiddenSingle->possibleValues.clear(); // empty that cell
                hiddenSingle->possibleValues.insert(values[n]); // insert single
                hiddenSingle->solved = true; // decide cell
                return true; // found a simplification
            } // if saw value only once
        } // for all values
    } // for all rows

    // iterate through the squares and check for values that only appear once
    for (int s = 0; s < 9; s++) { // for each square
        for (int n = 0; n < 9; n++) { // for each possible value
            
            seenOnlyOnce[n] = false; // initialize our "seen" array to once
            
            for (int i = (s/3)*3; i < (s/3)*3+3; i++){ // for the rows of square
            for (int j = (s%3)*3; j < (s%3)*3+3; j++){ // for the columns of square
                if (board[i][j].solved) { // if decided cell
                    if (board[i][j].findValue(values[n])) { // if has same value
                        seenOnlyOnce[n] = false;
                        i+=100; // ratchet skip to next square 
                        break;
                    } 
                    else
                        continue; // otherwise next cell
                } // if decided cell
                
                // Else, if we see the value
                if (board[i][j].findValue(values[n])) {
                    if(seenOnlyOnce[n]){ // if we've already seen it
                        seenOnlyOnce[n] = false; // no longer true
                        i+=100; // ratchet solution
                        break; // skip to next square
                    } // if already seen
                    else{ // otherwise, first time seeing the value
                        seenOnlyOnce[n] = true;
                        hiddenSingle = &board[i][j];
                    } // else
                } // if see value    
            }} // for each cell            
            if(seenOnlyOnce[n]){ // if saw the value only once
                hiddenSingle->possibleValues.clear(); // empty that cell
                hiddenSingle->possibleValues.insert(values[n]); // insert single
                hiddenSingle->solved = true; // decide cell
                return true; // found a simplification
            } // if saw value only once
        } // for all values
    } // for all squares
    
    return false; // if we don't find any =(
    
}// hiddenSingles()

/*
 * guess() takes in a copy of the current puzzle. It then searches for
 * "guessable" cells in order of probability of correct answer
 */
bool Puzzle:: guess(Puzzle &alternate) {
    // go through puzzle, check for impossible (empty) cells, then guess
    for (unsigned int n = 2, k = 2; n < 10; n++, k = n) { // from 2-9 possibilities
        for (int i = 0; i < 9; i++) { // for all rows
            for (int j = 0; j < 9; j++) { // for all columns
                // if the current cell has 'n' possibilities
                if (board[i][j].possibleValues.size() == n) {
                    while (--k) // erase all but last value
                        board[i][j].possibleValues.erase(board[i][j].possibleValues.begin());
                    board[i][j].solved = true; // "guess" that this is true
                    // next, erase this from our alternative board
                    alternate.board[i][j].possibleValues.erase(*(board[i][j].possibleValues.begin()));
                    return true;
                } // if
            } // for all columns
        } // for all rows
    } // from 2 - 9 possibilities
    
    return false;
} // guess()


/*
 * solved() returns TRUE if the puzzle is solved and FALSE otherwise.
 */
bool Puzzle::solved() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // if a cell is not solved OR impossible to solve
            if (!(board[i][j].solved) || board[i][j].possibleValues.empty())
                return false; // return false
        }// for all columns
    } // for all rows
    return true; // get this far, all cells must be solved
}


void Puzzle::printSolution() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << *board[i][j].possibleValues.begin();
        } // for all columns
    } // for all rows
    cout << endl;
} // printSolutions()

Puzzle Puzzle::operator=(const Puzzle &rhs) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = rhs.board[i][j];
        } // for all cells
    }
    return rhs;
}

bool Cell::findValue(const char value){
    if (possibleValues.find(value) != possibleValues.end())
        return true;
    return false;
}

Cell Cell::operator=(const Cell &rhs) {
    solved = rhs.solved;
    possibleValues = rhs.possibleValues;
    return rhs;
} // Cell operator=