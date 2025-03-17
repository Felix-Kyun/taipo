#include "taipo.h"
#include "word_generator.h"
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

Taipo *init_taipo(void) {
  // seed RNG
  srand(time(NULL));

  // init ncurses

  setlocale(LC_ALL, ""); // enable unicode
  initscr();             // init ncurses
  raw();                 // don't buffer input
  clear();               // clear screen
  noecho();              // don't echo input
  start_color();         // enable colors
  // curs_set(0);           // hide cursor
  box(stdscr, 0, 0);     // draw border
  use_default_colors();  // use terminal colors
  keypad(stdscr, TRUE);  // enable arrow keys
  nodelay(stdscr, TRUE); // non-blocking input
  immedok(stdscr, TRUE); // debug

  init_pair(1, COLOR_YELLOW, -1);
  init_pair(2, COLOR_GREEN, -1);
  init_pair(3, COLOR_RED, -1);

  Taipo *taipo = (Taipo *)malloc(sizeof(Taipo));
  taipo->gen = init_generator(10);
  generate_words(taipo->gen);
  display_words(taipo->gen);
  // clear_words(taipo->gen);
  taipo->current = 0;
  taipo->offset = 0;

  return taipo;
}

void free_taipo(Taipo *taipo) {
  free_generator(taipo->gen);
  free(taipo);

  endwin();
}

