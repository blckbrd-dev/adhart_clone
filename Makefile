all: main.cpp src/header/*.h 
	g++ -Wall -std=c++11 main.cpp src/header/*.h -lncurses -o main
run: all
	./main
