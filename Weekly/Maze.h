//Make the initial cell the current cell and mark it as visited
//While there are unvisited cells
//	If the current cell has any neighbours which have not been visited
//		Choose randomly one of the unvisited neighbours
//		Push the current cell to the stack
//		Remove the wall between the current cell and the chosen cell
//		Make the chosen cell the current cell and mark it as visited
//	Else if stack is not empty
//		Pop a cell from the stack
//		Make it the current cell

#include<tuple>
#include<vector>
#include<ostream>

namespace trolls {

struct Cell {

	Cell(int x, int y) : visited_(false), x_(x), y_(y) {};

	void Visited(bool b) { visited_ = b; }
	bool Visited() { return visited_; }

	std::tuple<int, int> GetCoordinates() { return std::make_tuple(x_, y_); }
	int GetX() { return x_; }
	int GetY() { return y_; }

	friend std::ostream& operator<<(std::ostream& os, Cell rhs) {
		return os << "{ " << rhs.x_ << ", " << rhs.y_ << " }" ;
	}

private:
	bool visited_;
	int x_, y_;
};

using Maze_t = std::vector<std::vector<Cell>>;

Maze_t GenerateMaze(int width, int height);

struct Maze {
private:
	int width_, height_;
	Maze_t cells_;

public:
	Maze(int width, int height) : width_(width), height_(height), cells_(GenerateMaze(width, height)) {}

	friend std::ostream& operator<<(std::ostream& os, Maze rhs) {
		for (auto&& row : rhs.cells_) {
			for (auto&& cell : row) {
				os << cell;
			}

			os << "\n";
		}

		os << std::endl;

		return os;
	}
};

} //trolls