#include <array>
#include <iostream>
#include <bitset>
#include <utility>
#include <random>
#include <tuple>

class Random {
private:
  std::mt19937 gen_{std::random_device{}()};

public:
  Random() = default;
  Random(std::mt19937::result_type seed) : gen_(seed) {}

  unsigned GenerateNumber(unsigned min, unsigned max) {
    return std::uniform_int_distribution<unsigned>{min, max}(gen_);
  }
};

// Declare statics
constexpr int s_N = 6;
//Cell: NESW <=> 0b1111
using Grid = std::array<std::array<std::bitset<4>, s_N>, s_N>;
Random s_rand;

void print_grid(Grid& g) {
  for(auto&& row : g) {
    for(auto&& col : row) {
      std::cout << col << "|";
    }

    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void generate( Grid& g, std::pair<int, int> pos ) {
  print_grid(g);
  int x = pos.first;
  int y = pos.second;
  // 1. Choose wall (adjacent cell))
  std::bitset<4> mask(0xf);
  mask &= g[x][y];

  std::vector<std::tuple<int,int,int>> adj_cells;
  if(!mask[0] && x > 0 )
    adj_cells.emplace_back(x - 1, y, 0);

  if(!mask[1] && y < s_N - 1 )
    adj_cells.emplace_back(x, y + 1, 1);

  if(!mask[2] && x < s_N - 1 )
    adj_cells.emplace_back(x + 1, y, 2);

  if(!mask[3] && y > 0 )
    adj_cells.emplace_back(x, y - 1, 3);

  if(adj_cells.size()) {
    auto rand_cell = adj_cells[ s_rand.GenerateNumber(0, adj_cells.size() - 1) ];
    std::pair<int, int> new_pos = { std::get<0>(rand_cell), std::get<1>(rand_cell) };
    g[pos.first][pos.second][std::get<2>(rand_cell)] = 1;
    generate(g, new_pos);
  };
}

int main(int argc, char const *argv[]) {
  // 1. Create N x N grid
  Grid grid;
  for(int i = 0; i < s_N; ++i) {
    for (int j = 0; j < s_N; ++j) {
      grid[i][j] = std::bitset<4>(0x0);
    }
  }

  // 2. Choose random starting point in grid
  std::pair<int, int> start = { s_rand.GenerateNumber(0, s_N - 1 ), s_rand.GenerateNumber(0, s_N - 1 ) };
  std::cout << "Start: " << start.first << " " << start.second << '\n';

  // 3. Choose wall and carve passage to adjacent cell if not yet visited
  generate(grid, start);

  return 0;
}
