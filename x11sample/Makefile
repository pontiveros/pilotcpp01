# Build prog01

#pilot01: main
#	mkdir bin; \
#	g++ -std=c++11 -o ./bin/pilot01 ./build/main.o
#	rm -rf ./build/*.o; \
#	rm -rf build

prog01: main.cpp
	#mkdir bin; \
	#g++ -std=c++11 -c -o ./build/main.o main.cpp
	gcc -Wall main.cpp -o test-x11 `pkg-config --cflags --libs xcb`

clean:
#	rm -rf ./build/*o ./bin/pilot01; \
#	rm -rf build; 
#	rm -rf bin
