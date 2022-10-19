CC = g++ -std=c++17 -Wall -Wextra -Werror
SUPPRESSES = --suppress=unusedFunction --suppress=syntaxError --suppress=missingInclude

test: test_build
	./testing.out
	rm -rf testing.out

test_build:
	$(CC) test.cpp ./model/cave.cpp ./model/Labyrinth.cpp ./model/finder.cpp -o testing.out -lgtest

static:
	cp ./../materials/linters/CPPLINT.cfg .
	-python3 ../materials/linters/cpplint.py Controller.cpp Controller.h ./model/*.cpp ./model/*.h
	-cppcheck --enable=all $(SUPPRESSES) --std=c++17 Controller.cpp Controller.h ./model/*.cpp ./model/*.h
	rm -rf CPPLINT.cfg

install: dvi
	-mkdir build
	qmake Controller.pro -o ./build/makefile_qt
	cd build && make -f makefile_qt
	open ./build

dist:
	mkdir -p dist
	tar --totals -cvf dist/Maze.tar .
	gzip dist/Maze.tar


uninstall: clear

clear:
	rm -rf build a.out

dvi:
	open ./readme.txt
