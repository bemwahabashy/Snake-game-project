/** Contains data structures for the snake game.
@file snake.h
@author Hong Tai Wei
*/

#include <deque>
#include <iostream>
#include <set>
#include <vector>

#ifndef SNAKE_H
#define SNAKE_H

constexpr int HEIGHT = 10;
constexpr int WIDTH = 20;
const int SPEED = 300;

enum Move {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  NONE,
};

/*

|---- x ---> (width)
|
y
|
v (height)

*/

struct Pos {
  int x;
  int y;
};

struct Snake {
  std::string id;
  int health;
  int length;
  Pos head;
  Move move;
  std::deque<Pos> body;
};

struct Game {
  std::vector<Snake> snakes;
  std::set<Pos> food;
  std::set<Pos> free;
  int turn;
};

inline bool operator==(const Pos& lhs, const Pos& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(const Pos& lhs, const Pos& rhs) { return !(lhs == rhs); }

inline bool operator<(const Pos& lhs, const Pos& rhs) {
  return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
}

inline std::ostream& operator<<(std::ostream& os, const Pos& p) {
  return os << "(" << p.x << ", " << p.y << ")";
}

inline std::ostream& operator<<(std::ostream& os, Move m) {
  switch (m) {
    case UP:
      return os << "up";
    case DOWN:
      return os << "down";
    case LEFT:
      return os << "left";
    case RIGHT:
      return os << "right";
    default:
      return os << "none";
  }
}

#endif  // SNAKE_H