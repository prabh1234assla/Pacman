run: compile
	./main.out
 
compile: main.cpp
	sudo g++ main.cpp -o main.out -lSDL2 -lSDL2_image