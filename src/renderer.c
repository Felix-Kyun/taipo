#include "renderer.h"
#include <ncurses.h>
#include <stdlib.h>

Renderer *renderer_init(void) {
  Renderer *renderer = (Renderer *)malloc(sizeof(Renderer));
  renderer->word_list = NULL;
  renderer->size = 0;
  renderer->current_word_index = 0;
  renderer->current_word_typing_size = 0;
  return renderer;
}

void renderer_update(Renderer *renderer, char **word_list, int size) {
  renderer->word_list = word_list;
  renderer->size = size;

  renderer->current_word_index = 0;
  renderer->current_word_typing_size = 0;
  renderer->correct_word_map = (int *)calloc(size, sizeof(int));
  renderer->current_word[0] = '\0';

}

// currently only supports one line rendering
void render(Renderer *renderer) {
  clear();

  int y, x;
  getmaxyx(stdscr, y, x);

  // move to center line
  move(y - 1, x - 1); // just to avoid compile error of x not being used, idk
                      // why it happens =_=
  move(y / 2, 10);

  // render word list {0: default, 1: correct, 2: incorrect}
  for (int i = 0; i < renderer->size; i++) {
    if (renderer->correct_word_map[i] == 0) {
      attron(COLOR_PAIR(1));
    } else if (renderer->correct_word_map[i] == 1) {
      attron(COLOR_PAIR(2));
    } else {
      attron(COLOR_PAIR(3));
    }

    printw("%s ", renderer->word_list[i]);

    if (renderer->correct_word_map[i] == 0) {
      attroff(COLOR_PAIR(1));
    } else if (renderer->correct_word_map[i] == 1) {
      attroff(COLOR_PAIR(2));
    } else {
      attroff(COLOR_PAIR(3));
    }
  }

  refresh();
}
