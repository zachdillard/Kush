ksh: myshell.o mycommands.o
	@g++ -g -o ksh myshell.o mycommands.o

myshell.o: myshell.cpp mycommands.h
	@g++ -Wc++11-compat-deprecated-writable-strings -c myshell.cpp

mycommands.o: mycommands.cpp mycommands.h
	@g++ -Wc++11-compat-deprecated-writable-strings -c mycommands.cpp
	
run:
	@./ksh
clean:
	@rm *.o ksh
