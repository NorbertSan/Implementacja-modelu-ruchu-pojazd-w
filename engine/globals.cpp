#include <vector>
#include <string>
#include "globals.hpp"

// needs to be even number
int BOARD_SIZE = 30;
int MAX_SPEED = 4;
int MAX_SPEED_IN_THE_CROSS = 1;

// in percentage
int RANDOM_BRAKING_PROBABILITY = 10;

std::string error = "";

std::string
get_error()
{
  return error;
}

int get_board_size()
{
  return BOARD_SIZE;
}

std::vector<int> get_down_right_road_indexes()
{
  std::vector<int> DOWN_RIGHT_ROAD;

  for (int i = (BOARD_SIZE / 2) - 2; i < BOARD_SIZE * BOARD_SIZE; i += BOARD_SIZE)
  {
    DOWN_RIGHT_ROAD.push_back(i);
  }

  return DOWN_RIGHT_ROAD;
}

std::vector<int> get_down_road_indexes()
{
  std::vector<int> DOWN_ROAD;

  for (int i = (BOARD_SIZE / 2) - 1; i < BOARD_SIZE * BOARD_SIZE; i += BOARD_SIZE)
  {
    DOWN_ROAD.push_back(i);
  }

  return DOWN_ROAD;
}

std::vector<int> get_up_road_indexes()
{
  std::vector<int> UP_ROAD;

  for (int i = (BOARD_SIZE / 2) + 1; i < BOARD_SIZE * BOARD_SIZE; i += BOARD_SIZE)
  {
    UP_ROAD.push_back(i);
  }

  return UP_ROAD;
}

std::vector<int> get_up_right_road_indexes()
{
  std::vector<int> UP_RIGHT_ROAD;

  for (int i = (BOARD_SIZE / 2) + 2; i < BOARD_SIZE * BOARD_SIZE; i += BOARD_SIZE)
  {
    UP_RIGHT_ROAD.push_back(i);
  }

  return UP_RIGHT_ROAD;
}

std::vector<int> get_right_road_indexes()
{
  std::vector<int> RIGHT_ROAD;
  for (int i = (BOARD_SIZE * (BOARD_SIZE + 2) / 2 - BOARD_SIZE); i < (BOARD_SIZE * (BOARD_SIZE + 2) / 2 - BOARD_SIZE) + BOARD_SIZE; i++)
  {
    RIGHT_ROAD.push_back(i);
  }

  return RIGHT_ROAD;
}

std::vector<int> get_right_right_road_indexes()
{
  std::vector<int> RIGHT_RIGHT_ROAD;

  for (int i = (BOARD_SIZE * (BOARD_SIZE + 2) / 2); i < (BOARD_SIZE * (BOARD_SIZE + 2) / 2) + BOARD_SIZE; i++)
  {
    RIGHT_RIGHT_ROAD.push_back(i);
  }

  return RIGHT_RIGHT_ROAD;
}

std::vector<int> get_left_road_indexes()
{
  std::vector<int> LEFT_ROAD;
  for (int i = (BOARD_SIZE * (BOARD_SIZE + 2) / 2 - 3 * BOARD_SIZE); i < (BOARD_SIZE * (BOARD_SIZE + 2) / 2 - 3 * BOARD_SIZE) + BOARD_SIZE; i++)
  {
    LEFT_ROAD.push_back(i);
  }

  return LEFT_ROAD;
}

std::vector<int> get_left_right_road_indexes()
{
  std::vector<int> LEFT_RIGHT_ROAD;
  for (int i = (BOARD_SIZE * (BOARD_SIZE + 2) / 2 - 4 * BOARD_SIZE); i < (BOARD_SIZE * (BOARD_SIZE + 2) / 2 - 4 * BOARD_SIZE) + BOARD_SIZE; i++)
  {
    LEFT_RIGHT_ROAD.push_back(i);
  }

  return LEFT_RIGHT_ROAD;
}

std::vector<int> get_middle_cell_indexes()
{
  // TODO: zahardkodowane, w tej konfiguracji to jest środek o wymiarach 5x5
  std::vector<int> MIDDLE_CELL_INDEXES;
  for (int i = 0; i < 5; i++)
    for (int j = 12 * BOARD_SIZE + (BOARD_SIZE / 2) - 2; j < 12 * BOARD_SIZE + (BOARD_SIZE / 2) + 3; j++)
    {
      MIDDLE_CELL_INDEXES.push_back(j + i * BOARD_SIZE);
    }

  return MIDDLE_CELL_INDEXES;
}

int get_index_for_down_direction_icon()
{
  return get_down_road_indexes()[0];
}

int get_index_for_down_right_direction_icon()
{
  return get_down_right_road_indexes()[0];
}

int get_index_for_up_direction_icon()
{
  return get_up_road_indexes().back();
}

int get_index_for_up_right_direction_icon()
{
  return get_up_right_road_indexes().back();
}

int get_index_for_right_direction_icon()
{
  return get_right_road_indexes()[0];
}

int get_index_for_right_right_direction_icon()
{
  return get_right_right_road_indexes()[0];
}

int get_index_for_left_direction_icon()
{
  return get_left_road_indexes().back();
}

int get_index_for_left_right_direction_icon()
{
  return get_left_right_road_indexes().back();
}

CELL_DIRECTION convert_int_to_cell_direction(int cell_direction)
{
  switch (cell_direction)
  {
  case 1:
    return CELL_DIRECTION::DOWN;
  case 2:
    return CELL_DIRECTION::UP;
  case 3:
    return CELL_DIRECTION::RIGHT;
  case 4:
    return CELL_DIRECTION::LEFT;
  default:
    return CELL_DIRECTION::DOWN;
  }
}
