#ifndef GLOBALS_H
#define GLOBALS_H

extern int BOARD_SIZE;

extern int MAX_POSSIBLE_SPEED;

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

int get_board_size();

int get_random_braking_probability();

void set_random_braking_probability(int NEW_RANDOM_BRAKING_PROBABILITY);

int get_max_possible_speed();

int get_max_speed();

void set_max_speed(int NEW_MAX_SPEED);

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