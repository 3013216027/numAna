CC=g++
core=interpolation

default: $(core).o
	$(CC) -std=c++11 -o cubic.exe ../../$(core).o main.cpp
	@echo "compile success!"
	@echo "run 'make run' for case test..."
	@sleep 1

run: cubic.exe
	./cubic.exe

$(core).o:
	$(CC) -std=c++11 -c -o ../../$(core).o ../../$(core).cpp

clean:
	rm -rf *.o
