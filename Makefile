sudsolve : main.o puzzle.o  
	g++ -ansi -Wall -g -o sudsolve main.o puzzle.o  

main.o : main.cpp puzzle.h 
	g++ -ansi -Wall -g -c main.cpp

puzzle.o : puzzle.cpp puzzle.h 
	g++ -ansi -Wall -g -c puzzle.cpp

clean : 
	rm -f sudsolve main.o  puzzle.o   
