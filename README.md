# Sudoku-Solver

"sudsolve" takes as input a sudoku puzzle as a single line
in row-major order  with empty squares listed as "."

example run:
--------------------------------------------------------------------------------------

$ sudsolve
..8.........63...4..1...63..3...9...4......62......14....5..79.17.........54...83

--------------------------------------------------------------------------------------- 

output is the solved puzzle or an error message if the
input is incorrect (or the puzzle unsolvable)


Install:
	make
Uninstall:
	make clean


Note: some versions of g++ disrupt input-checking


