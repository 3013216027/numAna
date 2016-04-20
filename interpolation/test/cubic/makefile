default: interpolation.o cubic1.o cubic2.o
	g++ -std=c++11 -O2 -o cubic1.exe cubic1.o interpolation.o
	g++ -std=c++11 -O2 -o cubic2.exe cubic2.o interpolation.o
	@echo "compile success!"
	@echo "run './cubic1.exe' and './cubic2.exe' for case test..."
	@sleep 1
	./cubic1.exe
	./cubic2.exe

interpolation.o: ../../interpolation.cpp
	g++ -std=c++11 -O2 -c ../../interpolation.cpp

cubic1.o: cubic1.cpp
	g++ -std=c++11 -O2 -c cubic1.cpp

cubic2.o: cubic2.cpp
	g++ -std=c++11 -O2 -c cubic2.cpp
