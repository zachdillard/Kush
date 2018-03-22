ksh: myshell.o mycommands.o
	g++ -o ksh myshell.o mycommands.o

myshell.o: myshell.cpp mycommands.h
	g++ -c myshell.cpp

mycommands.o: mycommands.cpp mycommands.h
	g++ -c mycommands.cpp
	
clean:
	rm *.o ksh
