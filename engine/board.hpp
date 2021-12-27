#include <vector>
#include <memory>
#include "cell.hpp"

#ifndef H_BOARD_HPP
#define H_BOARD_HPP

class Board
{

  std::vector<std::unique_ptr<Cell>> grid;
  std::vector<std::unique_ptr<Cell>> temp_grid;

public:
    Board();

    void update_positions();

    void generate_new_cars();

    std::vector<int> get_occupied_board();
};
#endif