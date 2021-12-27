#include <iostream>
#include "cell.hpp"

Cell::Cell(){
  is_occupied = false;
  speed = 0;
};

bool Cell::get_is_occupied(){
  return is_occupied;
};