
# Build pilotcpp01

pilot01: main
	mkdir bin; \
	g++ -std=c++11 -o ./bin/pilot01 ./build/main.o
	rm -rf ./build/*.o; \
	rm -rf build

main: main.cpp
	mkdir build; \
	g++ -std=c++11 -c -o ./build/main.o main.cpp

clean:
	rm -rf ./build/*o ./bin/pilot01; \
	rm -rf build; \
	rm -rf bin
