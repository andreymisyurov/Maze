#include <gtest/gtest.h>

#include <exception>
#include <stdexcept>
#include "./model/cave.h"
#include "./model/Labyrinth.h"
#include "./model/finder.h"

TEST(maze, example_1) {
  Labyrinth maze;
  maze.createLabyrinth(3, 3);
}

TEST(find, example_1) {
Labyrinth maze;
maze.createLabyrinth(3, 3);
Finder finder;
auto pair = maze.getLabyrinth();
finder.getPath(pair, 0, 0, 2, 2);
}

TEST(cave, example_1) {
  Cave cave(10, 5, 2, 5, 70);
  cave.generateField();
  cave.writeNeighbours();
  cave.lifeYear();
}

TEST(load_cave, example_1) {
Cave cave = Cave::loadCave("./examples/example6_cave.txt");
}

TEST(load_maze, example_1) {
Labyrinth maze;
maze.createLabyrinthFromFile("./examples/example1_maze.txt");
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

