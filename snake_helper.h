/** Header file for snake_helper.cpp.
@file snake.h
@author Hong Tai Wei
*/

#include <iostream>
#include <set>
#include <vector>
#include "lib/snake.h"

#ifndef SNAKE_HELPER_H
#define SNAKE_HELPER_H

// Given a 2D array that represents the board, draws the border walls using '#'.
void draw_walls(char board[HEIGHT + 2][WIDTH + 2]);

// Given a snake and a 2D array that represents the board, draws the snake head
// using '@' and the snake body using 'O'.
void draw_snake(char board[HEIGHT + 2][WIDTH + 2],
                const std::vector<Pos> snake);

// Given a set of food locations and a 2D array that represents the board, draws
// every piece of food using '+'.
void draw_food(char board[HEIGHT + 2][WIDTH + 2], const std::set<Pos> food);

// Given a snake and a pending move, returns whether the snake will collide with
// walls if the move is executed.
bool collide_walls(const std::vector<Pos> snake, Move move);

// Given a snake and a pending move, returns whether the snake will collide with
// itself if the move is executed.
bool collide_snake(const std::vector<Pos> snake, Move move);

// Given a snake, a pending move and a set of food positions, returns whether
// the snake will collide with any food if the move is executed.
bool collide_food(const std::vector<Pos> snake, Move move,
                  const std::set<Pos> food);

#endif  // SNAKE_HELPER_H