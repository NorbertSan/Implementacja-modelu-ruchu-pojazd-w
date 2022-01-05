#ifndef GLOBALS_H
#define GLOBALS_H

extern int BOARD_SIZE;

extern int MAX_SPEED;

extern int MAX_SPEED_IN_THE_CROSS;

extern int RANDOM_BRAKING_PROBABILITY;

extern std::string error;

enum CELL_DIRECTION
{
    NONE,
    DOWN,
    UP,
    RIGHT,
    LEFT,
};

enum TURNING_DIRECTION
{
    TURNING_LEFT,
    TURNING_RIGHT
};

// will be used to get board size from javascript code
int get_board_size();

std::string get_error();

std::vector<int> get_down_road_indexes();

std::vector<int> get_down_right_road_indexes();

std::vector<int> get_up_road_indexes();

std::vector<int> get_up_right_road_indexes();

std::vector<int> get_right_road_indexes();

std::vector<int> get_right_right_road_indexes();

std::vector<int> get_left_road_indexes();

std::vector<int> get_left_right_road_indexes();

std::vector<int> get_middle_cell_indexes();

int get_index_for_down_direction_icon();

int get_index_for_down_right_direction_icon();

int get_index_for_up_direction_icon();

int get_index_for_up_right_direction_icon();

int get_index_for_right_direction_icon();

int get_index_for_right_right_direction_icon();

int get_index_for_left_direction_icon();

int get_index_for_left_right_direction_icon();

CELL_DIRECTION convert_int_to_cell_direction(int cell_direction);

#endif