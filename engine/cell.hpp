#include "globals.hpp"
#include <vector>

#ifndef H_CELL_HPP
#define H_CELL_HPP

class Cell
{
  bool is_part_of_road;
  bool is_occupied;
  bool is_staying;
  bool is_first_turn;
  int speed;
  CELL_DIRECTION current_car_direction;
  CELL_DIRECTION desired_car_direction;

public:
  Cell(bool part_of_road);

  bool is_turning_required();
  TURNING_DIRECTION get_turning_direction();

  // getters
  bool get_is_occupied();
  bool get_is_part_of_road();
  int get_speed();
  bool get_is_staying();
  bool get_is_first_turn();
  CELL_DIRECTION get_current_car_direction();
  CELL_DIRECTION get_desired_car_direction();

  // setters
  void set_speed(int new_speed);
  void set_is_occupied(bool state);
  void set_current_car_direction(CELL_DIRECTION new_current_car_direction);
  void set_desired_car_direction(CELL_DIRECTION new_desired_car_direction);
  void set_is_staying(bool new_is_staying);
  void set_is_first_turn(bool new_is_first_turn);
};
#endif