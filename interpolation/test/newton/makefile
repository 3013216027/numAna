CC=g++
core=interpolation

default: $(core).o
	$(CC) -std=c++11 -o newton.exe ../../$(core).o newton.cpp
	@echo "compile success!"
	@echo "run 'make run' for case test..."
	@sleep 1

run: newton.exe
	./newton.exe

$(core).o:
	$(CC) -std=c++11 -c -o ../../$(core).o ../../$(core).cpp

clean:
	rm -rf *.o
