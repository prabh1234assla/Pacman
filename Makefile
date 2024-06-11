run: compile
	./main.out
 
compile: main.cpp
	g++ main.cpp -o main.out -lSDL2 -lSDL2_image

clear: ./main.out
	rm ./main.out