CC=g++
core=interpolation
name=e1_20

default: $(core).o
	$(CC) -std=c++11 -o $(name).exe ../$(core).o $(name).cpp
	@echo "compile success!"
	@echo "run 'make run' to run it:)"
	@sleep 1

run: $(name).exe
	./$(name).exe

$(core).o:
	$(CC) -std=c++11 -c -o ../$(core).o ../$(core).cpp

clean:
	rm -rf *.o
