INCLUDE	:= -Iinclude/
VERSION := 0.0.1
build: src/*.cpp
	rm -rf build && mkdir build
	g++ ./src/*.cpp $(INCLUDE) -o build/tracker$(VERSION).exe 

clean:
	rm -rf build

run:
	./build/tracker$(VERSION).exe