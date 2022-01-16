#include <vector>
#include <memory>
#include "cell.hpp"
#include "globals.hpp"

#ifndef H_BOARD_HPP
#define H_BOARD_HPP

class Board
{
  int generated_cars_amount;
  int current_cars_amount;
  bool simulation_status;
  std::vector<std::unique_ptr<Cell>> grid;
  std::vector<std::unique_ptr<Cell>> temp_grid;
  std::vector<int> middle_cell_indexes;
  std::vector<int> generated_cars_per_route;

  void align_grid_and_temp_grid();
  bool is_cell_in_the_middle_of_cross(int cell_index);
  int calculate_new_speed_riding_straight(CELL_DIRECTION direction, int cell_index);
  bool can_move_to_cell_in_the_middle(int desired_cell_index, CELL_DIRECTION current_car_direction, bool will_be_turning, bool is_already_in_the_middle);
  void increment_generated_cars_amount();
  void calculate_current_cars_amount();
  void increment_generated_cars_per_route(int route_index);

public:
  Board();

  // Exposed
  std::vector<int> get_generated_cars_per_route();
  int get_generated_cars_amount();
  int get_current_cars_amount();
  void update_positions();
  void generate_new_cars(int new_current_car_direction, int new_desired_car_direction);
  std::vector<int> get_occupied_board();
  std::vector<int> get_road_board();
  void set_simulation_status(bool new_simulation_status);
};
#endif