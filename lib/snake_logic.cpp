/** Contains logic for the Snake game.
@file snake_logic.cpp
@author Hong Tai Wei
*/

#include "snake_logic.h"
#include <iostream>
#include "../snake_helper.h"
#include "snake.h"
using namespace std;

const int START_LEN = 3;
const int START_HP = 100;
const int START_SPAWN = 3;
const int SPAWN_TIMER = 5;
const string PLAYER = "player";
const string BOT_PREFIX = "bot";

bool place_food(Game& game) {
  if (game.free.empty()) {
    return false;
  }

  int idx = rand() % game.free.size();
  Pos p = *next(game.free.begin(), idx);
  game.free.erase(p);
  game.food.insert(p);
  return true;
}

bool place_snake(Game& game, const string& id) {
  if (game.free.empty()) {
    return false;
  }

  // Check for id duplication
  for (const Snake& s : game.snakes) {
    if (s.id == id) {
      return false;
    }
  }

  int idx = rand() % game.free.size();
  Pos p = *next(game.free.begin(), idx);
  game.free.erase(p);

  Snake snake;
  snake.id = id;
  snake.health = START_HP;
  snake.length = START_LEN;
  snake.head = p;
  snake.move = p.x > (WIDTH + 1) / 2.0 ? LEFT : RIGHT;
  for (int i = 0; i < START_LEN; i++) {
    snake.body.push_front(p);
  }

  game.snakes.push_back(snake);
  return true;
}

void kill_snake(Game& game, Snake& s) {
  s.health = 0;
  for (const Pos& p : s.body) {
    game.free.insert(p);
  }
}

Game new_game(bool human_player, int num_bots) {
  Game game;
  game.turn = 0;

  for (int i = 1; i < HEIGHT + 1; i++) {
    for (int j = 1; j < WIDTH + 1; j++) {
      game.free.insert({.x = j, .y = i});
    }
  }

  if (human_player) {
    place_snake(game, PLAYER);
  }

  for (int i = 0; i < num_bots; i++) {
    place_snake(game, BOT_PREFIX + to_string(i));
  }

  for (int i = 0; i < START_SPAWN; i++) {
    place_food(game);
  }

  return game;
}

void take_turn(Game& game, Move player_move) {
  bool ongoing = false;
  for (Snake& s : game.snakes) {
    if (s.health <= 0 || s.id != PLAYER) {
      // Bots not yet implemented.
      continue;
    }

    if (player_move != NONE) {
      s.move = player_move;
    }

    ongoing = true;
    s.health--;

    vector<Pos> v = get_pos(s);
    if (collide_walls(v, s.move) || collide_snake(v, s.move)) {
      kill_snake(game, s);
      continue;
    }

    switch (s.move) {
      case UP:
        s.head.y--;
        break;
      case DOWN:
        s.head.y++;
        break;
      case LEFT:
        s.head.x--;
        break;
      case RIGHT:
        s.head.x++;
        break;
      default:
        break;
    }

    if (collide_food(v, s.move, game.food)) {
      game.food.erase(s.head);
      s.health = START_HP;
      s.length++;
    } else {
      game.free.insert(s.body.back());
      s.body.pop_back();
    }

    game.free.erase(s.head);
    s.body.push_front(s.head);
  }

  if (ongoing) {
    game.turn++;
    if (game.turn % SPAWN_TIMER == 0) {
      place_food(game);
    }
  }
}

vector<Pos> get_pos(const Snake& s) {
  vector<Pos> v;
  if (s.health > 0) {
    for (const Pos& p : s.body) {
      v.push_back(p);
    }
  }
  return v;
}