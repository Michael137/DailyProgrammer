#include "Maze.h"

trolls::Maze_t trolls::GenerateMaze(int width, int height) {
	trolls::Maze_t maze;

	for (int i = 0; i < height; ++i) {
		std::vector<Cell> tmp;
		for (int j = 0; j < width; ++j) {
			Cell c{ i,j };
			tmp.push_back(c);
		}
		maze.push_back(tmp);
	}

	return maze;
}