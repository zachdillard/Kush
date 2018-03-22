ksh: myshell.o mycommands.o
	g++ -Wall -g -o ksh myshell.o mycommands.o

myshell.o: myshell.cpp mycommands.h
	g++ -c myshell.cpp

mycommands.o: mycommands.cpp mycommands.h
	g++ -c mycommands.cpp
	
run:
	./ksh
clean:
	rm *.o ksh
