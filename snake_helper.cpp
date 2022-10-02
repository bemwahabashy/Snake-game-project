/** Contains helper functions for the snake game.
@file snake_helper.cpp
@author Bemwa Habashy
*/

#include "snake_helper.h"
#include <iostream>
#include <set>
#include <vector>
#include "lib/snake.h"
using namespace std;

void draw_walls(char board[HEIGHT + 2][WIDTH + 2]) {
  for (int i = 0; i < HEIGHT + 2; i++) {
    board[i][0] = '#';
    board[i][WIDTH + 1] = '#';
  }
  for (int i = 0; i < WIDTH + 2; i++) {
    board[0][i] = '#';
    board[HEIGHT + 1][i] = '#';
  }
}

void draw_snake(char board[HEIGHT + 2][WIDTH + 2],
                const std::vector<Pos> snake) {
  Pos p1;
  bool head = true;
  for (const Pos& i : snake) {
    if (head == true) {
      p1 = i;
      head = false;
    }
    if (i == p1) {
      board[i.y][i.x] = '@';
    } else {
      board[i.y][i.x] = 'O';
    }
  }
}

void draw_food(char board[HEIGHT + 2][WIDTH + 2], const std::set<Pos> food) {
  for (const Pos& i : food) {
    board[i.y][i.x] = '+';
  }
}

Pos find_head(const vector<Pos> snake, Move move) {
  Pos head = snake.front();
  if (move == UP) {
    head.y -= 1;
  } else if (move == DOWN) {
    head.y += 1;
  } else if (move == RIGHT) {
    head.x += 1;
  } else if (move == LEFT) {
    head.x -= 1;
  }
  return head;
}

bool collide_walls(const vector<Pos> snake, Move move) {
  if (snake.empty()) {
    return false;
  }

  Pos head = find_head(snake, move);
  if (head.x == 0 || head.y == 0 || head.x == WIDTH + 1 ||
      head.y == HEIGHT + 1) {
    return true;
  }
  return false;
}

bool collide_snake(const vector<Pos> snake, Move move) {
  if (snake.empty()) {
    return false;
  }
  Pos head = find_head(snake, move);
  for (const Pos& i : snake) {
    if (i == head) {
      return true;
    }
  }
  return false;
}

bool collide_food(const vector<Pos> snake, Move move, const set<Pos> food) {
  if (snake.empty()) {
    return false;
  }

  Pos head = find_head(snake, move);
  if (food.count(head) > 0) {
    return true;
  }

  return false;
}