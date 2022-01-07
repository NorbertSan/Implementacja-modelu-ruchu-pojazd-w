#include <vector>
#include <memory>
#include "cell.hpp"
#include "globals.hpp"

#ifndef H_BOARD_HPP
#define H_BOARD_HPP

class Board
{

  std::vector<std::unique_ptr<Cell>> grid;
  std::vector<std::unique_ptr<Cell>> temp_grid;
  // TODO: narazie nie uzywane
  std::vector<int> respawn_cell_indexes;
  std::vector<int> middle_cell_indexes;

  void align_grid_and_temp_grid();
  bool is_cell_in_the_middle_of_cross(int cell_index);
  int calculate_new_speed_riding_straight(CELL_DIRECTION direction, int cell_index);
  bool can_move_to_cell_in_the_middle(int desired_cell_index, CELL_DIRECTION current_car_direction, bool will_be_turning, bool is_already_in_the_middle);

public:
  Board();

  // Exposed
  void update_positions();
  void generate_new_cars(int new_current_car_direction, int new_desired_car_direction);
  std::vector<int> get_occupied_board();
  std::vector<int> get_road_board();
};
#endif