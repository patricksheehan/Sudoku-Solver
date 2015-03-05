// Patrick Sheehan

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "puzzle.h"
#include <cctype>
#include <stack>
#include <iomanip>

using namespace std;

bool findSolutions(Puzzle);


int main()
{
    unsigned char input[82]; // this will store  user input
    int i = 0;      // this will be used to iterate over input
    
    // loop through input and store it in our array
    // use cin.get() and unget because unsigned char was causing infinite loop
    while (cin.get() != EOF){ 
        cin.unget();
        input[i] = getchar();
        if (i == 81){ // check that this is actually the end of input
            if(input[i] == '\n'){ // if end
                i++;
                continue;
            } // if
            else // if not end, error
                cout << "ERROR: expected \\n saw ";
        } // if
        else if (i > 81) // if there is more input then we expect, error
            cout << "ERROR: expected <eof> saw ";
        // The following if checks for an allowed value of '.' or '1'-'9'
        else if (('.'==input[i]) || ((input[i] <= '9') && (input[i] > '0'))){
            i++; // iterate
            continue; // we've found an accepted value in an accepted location
        } //else if
        else
            cout << "ERROR: expected <value> saw ";
                  
        // if we've reached this point, we know there is an error
        // all that remains is to print what we saw
        if(isprint(input[i])) // if printable, just print what we saw
            cout << input[i] << endl;
        else if (input[i] == '\n')
            cout << "\\n" << endl;
        else // otherwise, print \x 2*<hexdigit> 
            cout << "\\x" << setw (2) << setfill ('0') << hex << (int) input[i] << endl;
        exit(0); // found an error, exit program
    }
   
    if (i < 81){ // if not enough input
        cout << "ERROR: expected <value> saw <eof>" << endl;
        exit(0);
    } // if not enough input
    
    Puzzle puzzle((char *) input); // now that we have correct input, make our puzzle
    if(!findSolutions(puzzle)) // if no solutions solutions found
        cout << "No solutions.\n"; // state such            
    
    exit(EXIT_SUCCESS);
} // main


bool findSolutions(Puzzle puzzle){
    stack<Puzzle> alternatives; // stack to store alternative puzzle choices
    alternatives.push(puzzle); // first alternative is the initial state
    bool simplificationFound; // to denote if we've simplified the puzzle
    bool solutionsFound;
    
    while(!alternatives.empty()){
        puzzle = alternatives.top(); // deal with next alternative puzzle
        alternatives.pop();
        
        while (puzzle.decideSingles()){} // right away find all possible singles
        
        simplificationFound = true;     // to get into the loop
        while (!puzzle.solved() && simplificationFound){
            simplificationFound = false; // now to check if we can simplify
            simplificationFound = puzzle.hiddenSingles();
            
            if (!simplificationFound){
                Puzzle alternative = puzzle; // set up alternative to our guess
                if ((simplificationFound = puzzle.guess(alternative)))
                    alternatives.push(alternative);
            }      
            if (simplificationFound)
                while (puzzle.decideSingles()){} // decide all singles          
        } // while puzzle not solved and simplifications still found
        
        if(puzzle.solved()){
            solutionsFound = true;
            puzzle.printSolution();
        } // if solution found    
    } // while alternative puzzle choices exist
    
    return solutionsFound;
}