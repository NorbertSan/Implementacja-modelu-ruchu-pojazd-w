#include <iostream>
#include "cell.hpp"
#include "globals.hpp"
#include <vector>

Cell::Cell(bool part_of_road)
{
  is_part_of_road = part_of_road;
  is_occupied = false;
  is_staying = false;
  speed = 0;
};

TURNING_DIRECTION Cell::get_turning_direction()
{
  if (current_car_direction == CELL_DIRECTION::LEFT && desired_car_direction == CELL_DIRECTION::UP)
    return TURNING_DIRECTION::TURNING_LEFT;

  if (current_car_direction == CELL_DIRECTION::LEFT && desired_car_direction == CELL_DIRECTION::DOWN)
    return TURNING_DIRECTION::TURNING_RIGHT;

  if (current_car_direction == CELL_DIRECTION::UP && desired_car_direction == CELL_DIRECTION::RIGHT)
    return TURNING_DIRECTION::TURNING_LEFT;

  if (current_car_direction == CELL_DIRECTION::UP && desired_car_direction == CELL_DIRECTION::LEFT)
    return TURNING_DIRECTION::TURNING_RIGHT;

  if (current_car_direction == CELL_DIRECTION::RIGHT && desired_car_direction == CELL_DIRECTION::DOWN)
    return TURNING_DIRECTION::TURNING_LEFT;

  if (current_car_direction == CELL_DIRECTION::RIGHT && desired_car_direction == CELL_DIRECTION::UP)
    return TURNING_DIRECTION::TURNING_RIGHT;

  if (current_car_direction == CELL_DIRECTION::DOWN && desired_car_direction == CELL_DIRECTION::LEFT)
    return TURNING_DIRECTION::TURNING_LEFT;

  if (current_car_direction == CELL_DIRECTION::DOWN && desired_car_direction == CELL_DIRECTION::RIGHT)
    return TURNING_DIRECTION::TURNING_RIGHT;
}

bool Cell::is_turning_required()
{
  return current_car_direction != desired_car_direction;
}

bool Cell::get_is_occupied()
{
  return is_occupied;
};

bool Cell::get_is_part_of_road()
{
  return is_part_of_road;
};

int Cell::get_speed()
{
  return speed;
};

CELL_DIRECTION Cell::get_current_car_direction()
{
  return current_car_direction;
};

CELL_DIRECTION Cell::get_desired_car_direction()
{
  return desired_car_direction;
};

bool Cell::get_is_staying()
{
  return is_staying;
};

bool Cell::get_is_first_turn()
{
  return is_first_turn;
};

void Cell::set_speed(int new_speed)
{
  speed = new_speed;
}

void Cell::set_is_occupied(bool state)
{
  is_occupied = state;
}

void Cell::set_current_car_direction(CELL_DIRECTION new_current_car_direction)
{
  current_car_direction = new_current_car_direction;
}

void Cell::set_desired_car_direction(CELL_DIRECTION new_desired_car_direction)
{
  desired_car_direction = new_desired_car_direction;
}

void Cell::set_is_staying(bool new_is_staying)
{
  is_staying = new_is_staying;
}

void Cell::set_is_first_turn(bool new_is_first_turn)
{
  is_first_turn = new_is_first_turn;
}
