run: compile
	./main
 
compile: main.cpp
	g++ main.cpp -o main -lSDL2 -lSDL2_image

clear: ./main
	rm ./main