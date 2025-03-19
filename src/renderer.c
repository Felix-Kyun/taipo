#include "renderer.h"
#include "cstring_vec.h"
#include <ncurses.h>
#include <stdlib.h>

Renderer *renderer_init(void) {
  Renderer *renderer = (Renderer *)malloc(sizeof(Renderer));
  renderer->word_list = vec_init();
  renderer->size = 0;
  renderer->current_word_index = 0;
  renderer->current_word_typing_size = 0;
  return renderer;
}

void renderer_update(Renderer *renderer, char **word_list, int size) {
  // renderer->word_list = word_list;
  renderer->size = size;

  renderer->current_word_index = 0;
  renderer->current_word_typing_size = 0;
  renderer->correct_word_map = (int *)calloc(size, sizeof(int));
  renderer->current_word[0] = '\0';

  getmaxyx(stdscr, renderer->y, renderer->x);

  // calc how many words will fit in one line + the space used by that line
  
  for (int i = 0; i < size; i++) {

    CString *word = cstring_from(word_list[i]);
    
    // put the word in the word list
    printw("%d\n", word->size);
    cstring_vec_push_back(renderer->word_list, word);
  }
}

// currently only supports one line rendering
void render(Renderer *renderer) {
  clear();

  // move to center line
  move(renderer->y / 2, 0);

  // render word list {0: default, 1: correct, 2: incorrect}
  for (int i = 0; i < renderer->size; i++) {
    if (renderer->correct_word_map[i] == 0) {
      attron(COLOR_PAIR(1));
    } else if (renderer->correct_word_map[i] == 1) {
      attron(COLOR_PAIR(2));
    } else {
      attron(COLOR_PAIR(3));
    }

    printw("%s ", cstring_vec_get(renderer->word_list, i)->str);

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
