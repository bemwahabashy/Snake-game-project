/** Runs Snake through the terminal.
@file snake_main.cpp
@author Hong Tai Wei
*/

#include <ncurses.h>
#include <chrono>
#include <iostream>
#include <set>
#include <thread>
#include "../snake_helper.h"
#include "snake.h"
#include "snake_logic.h"
using namespace std;

enum Input {
  IN_NONE,
  IN_UP,
  IN_DOWN,
  IN_LEFT,
  IN_RIGHT,
  IN_RESTART,
  IN_QUIT,
};

void setup() {
  // Init ncurses mode
  initscr();
  // Take one char at a time
  cbreak();
  // Suppress echo of typed chars
  noecho();
  // Capture special chars
  keypad(stdscr, true);
  // Don't block on user input
  nodelay(stdscr, true);
  // Hide cursor
  curs_set(0);
}

void tear_down() {
  // End ncurses mode
  endwin();
}

Move to_move(Input input) {
  switch (input) {
    case IN_UP:
      return UP;
    case IN_DOWN:
      return DOWN;
    case IN_LEFT:
      return LEFT;
    case IN_RIGHT:
      return RIGHT;
    default:
      return NONE;
  }
}

Input handle_input_turn(Game& game) {
  char ch;
  cin >> ch;
  switch (ch) {
    case 'w':
      return IN_UP;
    case 's':
      return IN_DOWN;
    case 'a':
      return IN_LEFT;
    case 'd':
      return IN_RIGHT;
    case 'c':
      return IN_NONE;
    case 'r':
      return IN_RESTART;
    default:
      return IN_QUIT;
  }
}

Input handle_input(Game& game) {
  int ch = getch();
  switch (ch) {
    case 'w':
    case 'W':
    case KEY_UP:
      return IN_UP;
    case 's':
    case 'S':
    case KEY_DOWN:
      return IN_DOWN;
    case 'a':
    case 'A':
    case KEY_LEFT:
      return IN_LEFT;
    case 'd':
    case 'D':
    case KEY_RIGHT:
      return IN_RIGHT;
    case 'r':
    case 'R':
      return IN_RESTART;
    case 'q':
    case 'Q':
      return IN_QUIT;
    default:
      return IN_NONE;
  }
}

void handle_output(const Game& game) {
  clear();
  char board[HEIGHT + 2][WIDTH + 2];
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      board[i][j] = ' ';
    }
  }
  draw_walls(board);
  draw_snake(board, get_pos(game.snakes[0]));
  draw_food(board, game.food);
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      mvprintw(i, j, "%c", board[i][j]);
    }
  }
  mvprintw(HEIGHT + 2, 0, "Snake - (R)estart (Q)uit - Turn: %i", game.turn);
  for (size_t i = 0; i < game.snakes.size(); i++) {
    int line = HEIGHT + 3 + i;
    move(line, 0);
    clrtoeol();
    const Snake& s = game.snakes[i];
    mvprintw(line, 0, "ID: %s - HP: %i - Length: %i", s.id.data(), s.health,
             s.length);
  }
  refresh();
}

void handle_output_turn(const Game& game) {
  char board[HEIGHT + 2][WIDTH + 2];
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      board[i][j] = ' ';
    }
  }
  draw_walls(board);
  draw_snake(board, get_pos(game.snakes[0]));
  draw_food(board, game.food);
  for (int i = 0; i < HEIGHT + 2; i++) {
    for (int j = 0; j < WIDTH + 2; j++) {
      cout << board[i][j];
    }
    cout << endl;
  }
  cout << "Snake - WASD (C)ontinue (R)estart (Q)uit - Turn: " << game.turn
       << endl;
  for (const Snake& s : game.snakes) {
    cout << "ID: " << s.id << " - HP: " << s.health << " - Length: " << s.length
         << endl;
  }
}

void real_time_main() {
  setup();
  Game game = new_game(1, 0);
  while (true) {
    Input input = handle_input(game);
    if (input == IN_RESTART) {
      game = new_game(1, 0);
      continue;
    } else if (input == IN_QUIT) {
      break;
    }
    take_turn(game, to_move(input));
    handle_output(game);
    this_thread::sleep_for(chrono::milliseconds(SPEED));
  }
  tear_down();
}

void turn_based_main() {
  Game game = new_game(1, 0);
  while (true) {
    handle_output_turn(game);
    Input input = handle_input_turn(game);
    if (input == IN_RESTART) {
      game = new_game(1, 0);
      continue;
    } else if (input == IN_QUIT) {
      break;
    }
    take_turn(game, to_move(input));
  }
}

int main() {
  cout << "Enter 1 for real-time snake, 0 for turn-based snake." << endl;
  bool real_time;
  cin >> real_time;

  srand(time(0));
  if (real_time) {
    real_time_main();
  } else {
    turn_based_main();
  }
}