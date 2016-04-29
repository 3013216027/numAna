default:
	@echo -e '\nUse "make <problem id>" to make & run,'
	@echo -e 'where <problem id> can be: "8"(for excise 4.8), "9"(for excise 4.9) or "1"(for computing excise 4.1)\n'

8:
	g++ -std=c++11 -O2 -o 4_8.exe 4_8.cpp
	@echo 'compile successfully!'
	./4_8.exe

9:
	g++ -std=c++11 -O2 -o 4_9.exe 4_9.cpp
	@echo 'compile successfully!'
	./4_9.exe

1:
	@echo 'generating data for e4_1...'
	g++ -std=c++11 -O2 -o e4_1_generator.exe e4_1_generator.cpp
	./e4_1_generator.exe | tee e4_1.in
	g++ -std=c++11 -O2 -o e4_1.exe e4_1.cpp
	@echo 'compile successfully! running now...'
	./e4_1.exe
