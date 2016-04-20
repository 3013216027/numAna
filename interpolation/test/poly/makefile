CC=g++
core=interpolation

default: $(core).o
	$(CC) -std=c++11 -o poly.exe ../../$(core).o main.cpp
	@echo "compile success!"
	@echo "run 'make run' for case test..."
	@sleep 1

run: poly.exe
	@./poly.exe < case.txt

$(core).o:
	$(CC) -std=c++11 -c -o ../../$(core).o ../../$(core).cpp

clean:
	rm -rf *.o
