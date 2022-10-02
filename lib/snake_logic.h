/** Header file for snake_logic.cpp.
@file snake_logic.h
@author Hong Tai Wei
*/

#include <iostream>
#include "snake.h"

#ifndef SNAKE_LOGIC_H
#define SNAKE_LOGIC_H

Game new_game(bool human_player, int num_bots);
void take_turn(Game& game, Move player_move);
std::vector<Pos> get_pos(const Snake& s);

#endif  // SNAKE_LOGIC_H