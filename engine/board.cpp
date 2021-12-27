#include <iostream>
#include <vector>
#include "board.hpp"
#include "cell.hpp"
#include <memory>
#include "globals.hpp"

Board::Board(){
  for(int i=0; i<BOARD_SIZE; ++i){
    Cell cell = Cell();
    grid.push_back(std::make_unique<Cell>());
  } 
};

void Board::update_positions(){};

void Board::generate_new_cars(){};

std::vector<int> Board::get_occupied_board(){
  std::vector<int> occupied_board;

  for(int i=0; i < grid.size(); i++){
    int is_occupied = grid[i]->get_is_occupied() == true ? 1 : 0;
    occupied_board.push_back(is_occupied);
  }

  return occupied_board;
};
