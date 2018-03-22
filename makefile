ksh: myshell.o mycommands.o
	@g++ -w -g -o ksh myshell.o mycommands.o

myshell.o: myshell.cpp mycommands.h
	@g++ -w -c myshell.cpp

mycommands.o: mycommands.cpp mycommands.h
	@g++ -w -c mycommands.cpp
	
run:
	@./ksh
clean:
	@rm *.o ksh
