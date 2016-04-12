default: compile

compile: interpolation.h interpolation.cpp main.cpp
	g++ -std=c++11 -o main main.cpp

run: main.exe
	./main.exe

clean:
	rm -rf main.exe *.o
