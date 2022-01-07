#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include "board.hpp"
#include "cell.hpp"
#include <memory>
#include "globals.hpp"
#include <algorithm>

void Board::align_grid_and_temp_grid()
{
  for (int j = 0; j < grid.size(); ++j)
  {
    int new_speed = temp_grid[j]->get_speed();
    bool new_is_occupied = temp_grid[j]->get_is_occupied();
    CELL_DIRECTION new_current_car_direction = temp_grid[j]->get_current_car_direction();
    CELL_DIRECTION new_desired_car_direction = temp_grid[j]->get_desired_car_direction();
    bool new_is_staying = temp_grid[j]->get_is_staying();

    grid[j]->set_speed(new_speed);
    grid[j]->set_is_occupied(new_is_occupied);
    grid[j]->set_current_car_direction(new_current_car_direction);
    grid[j]->set_desired_car_direction(new_desired_car_direction);
    grid[j]->set_is_staying(new_is_staying);
  }
}

Board::Board()
{
  middle_cell_indexes = get_middle_cell_indexes();

  for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
  {
    std::vector<int> DOWN_ROAD = get_down_road_indexes();
    std::vector<int> DOWN_RIGHT_ROAD = get_down_right_road_indexes();
    std::vector<int> UP_ROAD = get_up_road_indexes();
    std::vector<int> UP_RIGHT_ROAD = get_up_right_road_indexes();
    std::vector<int> RIGHT_ROAD = get_right_road_indexes();
    std::vector<int> RIGHT_RIGHT_ROAD = get_right_right_road_indexes();
    std::vector<int> LEFT_ROAD = get_left_road_indexes();
    std::vector<int> LEFT_RIGHT_ROAD = get_left_right_road_indexes();

    std::vector<CELL_DIRECTION> cell_directions;

    if (std::count(DOWN_ROAD.begin(), DOWN_ROAD.end(), i))
      cell_directions.push_back(CELL_DIRECTION::DOWN);

    if (std::count(DOWN_RIGHT_ROAD.begin(), DOWN_RIGHT_ROAD.end(), i))
    {
      cell_directions.push_back(CELL_DIRECTION::DOWN);
      cell_directions.push_back(CELL_DIRECTION::LEFT);
    }

    if (std::count(UP_ROAD.begin(), UP_ROAD.end(), i))
      cell_directions.push_back(CELL_DIRECTION::UP);

    if (std::count(UP_RIGHT_ROAD.begin(), UP_RIGHT_ROAD.end(), i))
    {
      cell_directions.push_back(CELL_DIRECTION::UP);
      cell_directions.push_back(CELL_DIRECTION::RIGHT);
    }

    if (std::count(RIGHT_ROAD.begin(), RIGHT_ROAD.end(), i))
      cell_directions.push_back(CELL_DIRECTION::RIGHT);

    if (std::count(RIGHT_RIGHT_ROAD.begin(), RIGHT_RIGHT_ROAD.end(), i))
    {
      cell_directions.push_back(CELL_DIRECTION::RIGHT);
      cell_directions.push_back(CELL_DIRECTION::DOWN);
    }

    if (std::count(LEFT_ROAD.begin(), LEFT_ROAD.end(), i))
      cell_directions.push_back(CELL_DIRECTION::LEFT);

    if (std::count(LEFT_RIGHT_ROAD.begin(), LEFT_RIGHT_ROAD.end(), i))
    {
      cell_directions.push_back(CELL_DIRECTION::LEFT);
      cell_directions.push_back(CELL_DIRECTION::UP);
    }

    if (cell_directions.size() > 0)
    {
      temp_grid.push_back(std::make_unique<Cell>(true));
      grid.push_back(std::make_unique<Cell>(true));
    }
    else
    {
      std::vector<CELL_DIRECTION> empty_directions;
      temp_grid.push_back(std::make_unique<Cell>(false));
      grid.push_back(std::make_unique<Cell>(false));
    }
  }
};

bool Board::can_move_to_cell_in_the_middle(int desired_cell_index, CELL_DIRECTION current_car_direction, bool will_be_turning, bool is_already_in_the_middle)
{
  // wystarczy sprawdzic docelowa komorke plus tyle sasiadow co MAX_SPEED_IN_THE_CROSS
  // wtedy mamy pewnosc, ze jezeli nawet jakies auto jest na skrzyzowaniu
  // to nie bedzie kolizji bo ma ograniczona predkosc
  bool can_move = true;

  if (will_be_turning)
  {
    int neighbour_cells_need_to_check = MAX_SPEED_IN_THE_CROSS + 1;
    for (int i = 0; i < neighbour_cells_need_to_check; i++)
    {
      int cell_index_to_check;
      if (current_car_direction == CELL_DIRECTION::DOWN)
        cell_index_to_check = desired_cell_index + i;

      else if (current_car_direction == CELL_DIRECTION::UP)
        cell_index_to_check = desired_cell_index - i;

      else if (current_car_direction == CELL_DIRECTION::LEFT)
        cell_index_to_check = desired_cell_index - (i * BOARD_SIZE);

      else if (current_car_direction == CELL_DIRECTION::RIGHT)
        cell_index_to_check = desired_cell_index + (i * BOARD_SIZE);

      if (grid[cell_index_to_check]->get_is_occupied())
      {
        can_move = false;
        break;
      }
    }
  }
  else
  {
    // is_already_in_the_middle posłuzy do zastosowanie reguly prawej reki i unikniecia sytuacji gdzie dwa auta sie zablokuja wzajemnie
    // tutaj spradzam tylko czy sa pojazdy naprzeciwko i po prawej stronie, po lewej stronie mnie nie intersuje
    if (is_already_in_the_middle)
    {
      int neighbour_cells_need_to_check = MAX_SPEED_IN_THE_CROSS + 1;
      for (int i = 0; i < neighbour_cells_need_to_check; i++)
      {
        int cell_index_to_check;

        if (current_car_direction == CELL_DIRECTION::DOWN)
        {
          cell_index_to_check = desired_cell_index + i - 1;
        }
        else if (current_car_direction == CELL_DIRECTION::UP)
        {
          cell_index_to_check = desired_cell_index + i;
        }
        else if (current_car_direction == CELL_DIRECTION::LEFT)
        {
          cell_index_to_check = desired_cell_index - i * BOARD_SIZE;
        }
        else if (current_car_direction == CELL_DIRECTION::RIGHT)
        {
          cell_index_to_check = desired_cell_index + i * BOARD_SIZE;
        }

        if (grid[cell_index_to_check]->get_is_occupied())
        {
          can_move = false;
          break;
        }
      }
    }
    // tutaj trzeba sprawdzic wszystkie kierunki poniewaz, zasada prawej reki bedzie dzialac dopiero jak wjedzie na skrzyzowanie
    else
    {
      int neighbour_cells_need_to_check = MAX_SPEED_IN_THE_CROSS + 2;

      for (int i = 0; i < neighbour_cells_need_to_check; i++)
      {
        int cell_index_to_check_first_row;
        // chyba nie potrzebne, do sprawdzenia
        int cell_index_to_check_second_row;

        if (current_car_direction == CELL_DIRECTION::DOWN)
        {
          cell_index_to_check_first_row = desired_cell_index + i - 1;
          cell_index_to_check_second_row = desired_cell_index + i - 1 + BOARD_SIZE;
        }
        else if (current_car_direction == CELL_DIRECTION::UP)
        {
          cell_index_to_check_first_row = desired_cell_index + i - 1;
          cell_index_to_check_second_row = desired_cell_index + i - 1 - BOARD_SIZE;
        }
        else if (current_car_direction == CELL_DIRECTION::LEFT)
        {
          cell_index_to_check_first_row = desired_cell_index + (i - 1) * BOARD_SIZE;
          cell_index_to_check_second_row = desired_cell_index + (i - 1) * BOARD_SIZE - 1;
        }
        else if (current_car_direction == CELL_DIRECTION::RIGHT)
        {
          cell_index_to_check_first_row = desired_cell_index + (i - 1) * BOARD_SIZE;
          cell_index_to_check_second_row = desired_cell_index + (i - 1) * BOARD_SIZE + 1;
        }

        if (grid[cell_index_to_check_first_row]->get_is_occupied() || grid[cell_index_to_check_second_row]->get_is_occupied())
        {
          can_move = false;
          break;
        }
      }
    }
  }

  return can_move;
}

bool Board::is_cell_in_the_middle_of_cross(int cell_index)
{
  if (std::count(middle_cell_indexes.begin(), middle_cell_indexes.end(), cell_index))
    return true;
  else
    return false;
}

int Board::calculate_new_speed_riding_straight(CELL_DIRECTION direction, int cell_index)
{
  // nie potrzeba wiedziec czy jest wiecej wolnych komorek niz max speed
  int free_cells = MAX_SPEED;

  for (int i = 0; i <= MAX_SPEED; i++)
  {
    if (direction == CELL_DIRECTION::RIGHT)
    {
      if (grid[cell_index + i + 1]->get_is_occupied())
      {
        free_cells = i;
        break;
      }
    }

    if (direction == CELL_DIRECTION::LEFT)
    {
      if (grid[cell_index - i - 1]->get_is_occupied())
      {
        free_cells = i;
        break;
      }
    }

    if (direction == CELL_DIRECTION::DOWN)
    {
      if (grid[cell_index + (i * BOARD_SIZE) + BOARD_SIZE]->get_is_occupied())
      {
        free_cells = i;
        break;
      }
    }

    if (direction == CELL_DIRECTION::UP)
    {
      if (grid[cell_index - (i * BOARD_SIZE) - BOARD_SIZE]->get_is_occupied())
      {
        free_cells = i;
        break;
      }
    }
  }

  int old_speed = grid[cell_index]->get_speed();
  int new_speed;

  if (old_speed + 1 >= MAX_SPEED)
    new_speed = MAX_SPEED;
  else
    new_speed = old_speed + 1;

  if (new_speed > free_cells)
    new_speed = free_cells;

  // losowe hamowanie gdy jedzie ponad 1
  if (new_speed > 1 && rand() % 99 <= RANDOM_BRAKING_PROBABILITY)
    new_speed--;

  return new_speed;
}

void Board::update_positions()
{
  srand(time(NULL));
  std::string temp_error;

  for (int i = 0; i < grid.size(); ++i)
  {
    if (!grid[i]->get_is_occupied())
      continue;

    if (grid[i]->get_is_first_turn())
    {
      grid[i]->set_is_first_turn(false);
      continue;
    }

    CELL_DIRECTION old_current_car_direction = grid[i]->get_current_car_direction();
    CELL_DIRECTION old_desired_car_direction = grid[i]->get_desired_car_direction();
    bool new_is_staying = grid[i]->get_is_staying();

    // porusz się: wyczyść starą pozycje i ustaw nową w temp_grid
    temp_grid[i]->set_speed(0);
    temp_grid[i]->set_is_occupied(false);
    temp_grid[i]->set_is_staying(false);
    temp_grid[i]->set_current_car_direction(CELL_DIRECTION::NONE);
    temp_grid[i]->set_desired_car_direction(CELL_DIRECTION::NONE);

    int new_cell_position_index;
    bool check_if_out_of_horizontal_road = false;
    int start_index_horizontal_road;
    int end_index_horizontal_road;
    bool has_turned_in_this_round = false;

    // TODO: zrobić hamowanie gdy auto zbliza się do srodka skrzyzowanie
    // moze mozna ustalić, ze gdy auto skreca max predkość 2
    // a gdy jedzie prosto max predkość 3
    // mialoby to uzasadnienie poniewaz na skrzyzowanie trzeba zachowac ostrozność

    int new_calculated_speed;

    switch (grid[i]->get_current_car_direction())
    {
    case CELL_DIRECTION::DOWN:
      new_calculated_speed = calculate_new_speed_riding_straight(CELL_DIRECTION::DOWN, i);
      new_cell_position_index = i + new_calculated_speed * BOARD_SIZE;
      break;

    case CELL_DIRECTION::UP:
      new_calculated_speed = calculate_new_speed_riding_straight(CELL_DIRECTION::UP, i);
      new_cell_position_index = i - new_calculated_speed * BOARD_SIZE;
      break;

    case CELL_DIRECTION::RIGHT:
      new_calculated_speed = calculate_new_speed_riding_straight(CELL_DIRECTION::RIGHT, i);
      check_if_out_of_horizontal_road = true;
      start_index_horizontal_road = floor(i / BOARD_SIZE) * BOARD_SIZE;
      end_index_horizontal_road = (floor(i / BOARD_SIZE) + 1) * BOARD_SIZE;
      new_cell_position_index = i + new_calculated_speed;
      break;

    case CELL_DIRECTION::LEFT:
      new_calculated_speed = calculate_new_speed_riding_straight(CELL_DIRECTION::LEFT, i);
      check_if_out_of_horizontal_road = true;
      start_index_horizontal_road = floor(i / BOARD_SIZE) * BOARD_SIZE;
      end_index_horizontal_road = (floor(i / BOARD_SIZE) + 1) * BOARD_SIZE;
      new_cell_position_index = i - new_calculated_speed;
      break;

    default:
      break;
    }

    // sprawdz czy nastepna pozycja będzie na srodku skrzyzowania
    if (is_cell_in_the_middle_of_cross(new_cell_position_index))
    {
      // ustaw na pierwszym miejscu przed skrzyzowaniem
      if (!new_is_staying)
      {
        int i_temp = i;
        int first_empty_cell_index;
        while (true)
        {
          if (is_cell_in_the_middle_of_cross(i_temp))
          {
            new_cell_position_index = first_empty_cell_index;
            new_calculated_speed = 0;
            new_is_staying = true;
            break;
          }
          first_empty_cell_index = i_temp;

          if (grid[i]->get_current_car_direction() == CELL_DIRECTION::LEFT)
            i_temp--;
          if (grid[i]->get_current_car_direction() == CELL_DIRECTION::RIGHT)
            i_temp++;
          if (grid[i]->get_current_car_direction() == CELL_DIRECTION::DOWN)
            i_temp += BOARD_SIZE;
          if (grid[i]->get_current_car_direction() == CELL_DIRECTION::UP)
            i_temp -= BOARD_SIZE;
        }
      }
      else
      {
        if (grid[i]->is_turning_required())
        {
          // ustawiam na i, bo jezeli sie nie zmieni, znaczy,ze auto nie moze sie ruszyc i musi zostac w tym samym miejscu
          new_cell_position_index = i;
          new_calculated_speed = 0;
          int desired_cell_index;

          if (grid[i]->get_current_car_direction() == CELL_DIRECTION::DOWN)
            desired_cell_index = i + BOARD_SIZE;
          else if (grid[i]->get_current_car_direction() == CELL_DIRECTION::UP)
            desired_cell_index = i - BOARD_SIZE;
          else if (grid[i]->get_current_car_direction() == CELL_DIRECTION::LEFT)
            desired_cell_index = i - 1;
          else if (grid[i]->get_current_car_direction() == CELL_DIRECTION::RIGHT)
            desired_cell_index = i + 1;

          if (can_move_to_cell_in_the_middle(desired_cell_index, grid[i]->get_current_car_direction(), true, false))
          {
            new_cell_position_index = desired_cell_index;
            has_turned_in_this_round = true;
            new_is_staying = false;
          }
        }
        // jedzie na wprost i chce wjechac na srodek skrzyzowania
        else
        {
          // ustawiam na i, bo jezeli sie nie zmieni, znaczy,ze auto nie moze sie ruszyc i musi zostac w tym samym miejscu
          new_cell_position_index = i;
          new_calculated_speed = 0;
          int desired_cell_index;

          if (grid[i]->get_current_car_direction() == CELL_DIRECTION::LEFT)
            desired_cell_index = i - 1;
          else if (grid[i]->get_current_car_direction() == CELL_DIRECTION::RIGHT)
            desired_cell_index = i + 1;
          else if (grid[i]->get_current_car_direction() == CELL_DIRECTION::DOWN)
            desired_cell_index = i + BOARD_SIZE;
          else if (grid[i]->get_current_car_direction() == CELL_DIRECTION::UP)
            desired_cell_index = i - BOARD_SIZE;

          bool is_old_position_in_the_middle = is_cell_in_the_middle_of_cross(i);

          if (can_move_to_cell_in_the_middle(desired_cell_index, grid[i]->get_current_car_direction(), false, is_old_position_in_the_middle))
          {
            new_cell_position_index = desired_cell_index;
            if (!is_cell_in_the_middle_of_cross(new_cell_position_index))
              new_is_staying = false;
          }
        }
      }
    }

    // sprawdź czy czasem nie jest poza planszą
    // 1. nowy indeks musi byc mniejszy niz maksymalny element tabicy
    // 2. nowy indeks musi byc wiekszy niz -1
    // 3. jezeli jedzie na wprost, sprawdz czy auto nie wyjechalo poza droge

    if (new_cell_position_index < BOARD_SIZE * BOARD_SIZE && new_cell_position_index > -1 && (check_if_out_of_horizontal_road ? (new_cell_position_index >= start_index_horizontal_road && new_cell_position_index < end_index_horizontal_road) : true))
    {
      if (temp_grid[new_cell_position_index]->get_is_occupied())
      {
        int old_speed = grid[i]->get_speed();
        temp_error = "Kolizja na pozycji:" + std::to_string(new_cell_position_index) + "! Stara pozycja:" + std::to_string(i) + ", nowa pozycja:" + std::to_string(new_cell_position_index) + ", stara predkosc::" + std::to_string(old_speed) + ", nowa predkosc:" + std::to_string(new_calculated_speed);
      }

      temp_grid[new_cell_position_index]->set_is_occupied(true);
      temp_grid[new_cell_position_index]->set_desired_car_direction(old_desired_car_direction);
      temp_grid[new_cell_position_index]->set_speed(new_calculated_speed);
      temp_grid[new_cell_position_index]->set_is_staying(new_is_staying);

      if (has_turned_in_this_round)
      {
        temp_grid[new_cell_position_index]->set_current_car_direction(old_desired_car_direction);
      }
      else
      {
        temp_grid[new_cell_position_index]->set_current_car_direction(old_current_car_direction);
      }
    }
  }

  error = temp_error;

  align_grid_and_temp_grid();
};

void Board::generate_new_cars(int new_current_car_direction_number, int new_desired_car_direction_number)
{
  //  TODO: check whether cell for new car is occupied !
  // 13, 14, 886, 887,450, 480, 389,419

  CELL_DIRECTION new_current_car_direction = convert_int_to_cell_direction(new_current_car_direction_number);
  CELL_DIRECTION new_desired_car_direction = convert_int_to_cell_direction(new_desired_car_direction_number);

  int cell_index;

  // 1
  if (new_current_car_direction == CELL_DIRECTION::DOWN && new_desired_car_direction == CELL_DIRECTION::LEFT)
  {
    cell_index = 13;
    // new_desired_car_direction = CELL_DIRECTION::DOWN;
  }
  // 2
  else if (new_current_car_direction == CELL_DIRECTION::DOWN && new_desired_car_direction == CELL_DIRECTION::DOWN)
    cell_index = 14;
  // 3
  else if (new_current_car_direction == CELL_DIRECTION::LEFT && new_desired_car_direction == CELL_DIRECTION::UP)
  {
    // new_desired_car_direction = CELL_DIRECTION::LEFT;
    cell_index = 389;
  }
  // 4
  else if (new_current_car_direction == CELL_DIRECTION::LEFT && new_desired_car_direction == CELL_DIRECTION::LEFT)
    cell_index = 419;
  // 5
  else if (new_current_car_direction == CELL_DIRECTION::UP && new_desired_car_direction == CELL_DIRECTION::RIGHT)
  {
    cell_index = 887;
    // new_desired_car_direction = CELL_DIRECTION::UP;
  }
  // 6
  else if (new_current_car_direction == CELL_DIRECTION::UP && new_desired_car_direction == CELL_DIRECTION::UP)
    cell_index = 886;
  // 7
  else if (new_current_car_direction == CELL_DIRECTION::RIGHT && new_desired_car_direction == CELL_DIRECTION::DOWN)
  {
    cell_index = 480;
    // new_desired_car_direction = CELL_DIRECTION::RIGHT;
  }
  // 8
  else if (new_current_car_direction == CELL_DIRECTION::RIGHT && new_desired_car_direction == CELL_DIRECTION::RIGHT)
    cell_index = 450;

  if (grid[cell_index]->get_is_occupied())
    return;

  int random_speed = rand() % MAX_SPEED;

  grid[cell_index]->set_speed(random_speed);
  grid[cell_index]->set_is_occupied(true);
  grid[cell_index]->set_current_car_direction(new_current_car_direction);
  grid[cell_index]->set_desired_car_direction(new_desired_car_direction);
  grid[cell_index]->set_is_first_turn(true);

  temp_grid[cell_index]->set_speed(random_speed);
  temp_grid[cell_index]->set_is_occupied(true);
  temp_grid[cell_index]->set_current_car_direction(new_current_car_direction);
  temp_grid[cell_index]->set_desired_car_direction(new_desired_car_direction);
  temp_grid[cell_index]->set_is_first_turn(true);
};

std::vector<int> Board::get_occupied_board()
{
  std::vector<int> occupied_board;

  for (int i = 0; i < grid.size(); i++)
  {
    int is_occupied = grid[i]->get_is_occupied() == true ? 1 : 0;
    occupied_board.push_back(is_occupied);
  }

  return occupied_board;
};

std::vector<int> Board::get_road_board()
{
  std::vector<int> road_board;

  for (int i = 0; i < grid.size(); ++i)
  {
    int is_part_of_road = grid[i]->get_is_part_of_road() == true ? 1 : 0;
    road_board.push_back(is_part_of_road);
  }

  return road_board;
};
