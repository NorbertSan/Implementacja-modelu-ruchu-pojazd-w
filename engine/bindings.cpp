#include <emscripten/bind.h>
#include "board.hpp"
#include "globals.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(board_module)
{
    register_vector<int>("VectorInt");

    class_<Board>("Board")
        .constructor()
        .function("update_positions", &Board::update_positions)
        .function("generate_new_cars", &Board::generate_new_cars)
        .function("get_occupied_board", &Board::get_occupied_board, allow_raw_pointer<arg<0>>())
        .function("get_road_board", &Board::get_road_board, allow_raw_pointer<arg<0>>());
}

EMSCRIPTEN_BINDINGS(globals)
{
    function("get_board_size", &get_board_size);
    function("get_index_for_down_direction_icon", &get_index_for_down_direction_icon);
    function("get_index_for_down_right_direction_icon", &get_index_for_down_right_direction_icon);
    function("get_index_for_up_direction_icon", &get_index_for_up_direction_icon);
    function("get_index_for_up_right_direction_icon", &get_index_for_up_right_direction_icon);
    function("get_index_for_right_direction_icon", &get_index_for_right_direction_icon);
    function("get_index_for_right_right_direction_icon", &get_index_for_right_right_direction_icon);
    function("get_index_for_left_direction_icon", &get_index_for_left_direction_icon);
    function("get_index_for_left_right_direction_icon", &get_index_for_left_right_direction_icon);
    function("get_middle_cell_indexes", &get_middle_cell_indexes);
    function("get_error", &get_error);
}