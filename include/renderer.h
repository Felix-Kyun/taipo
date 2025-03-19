#ifndef __TAIPO__RENDERER_H__
#define __TAIPO__RENDERER_H__

#include "vec.h"
typedef struct Renderer {
  // store the array of words to be typed 
  // char **word_list;
  Vec *word_list;

  // the size of the above array 
  int size;

  // index of the word being typed
  int current_word_index;

  // shows if the words have been typed correctly 
  // this handles the coloring of the words
  // 0: default(pair0), 1: correct(pair1), 2: incorrect (pair2)
  int *correct_word_map;

  // screen dimensions
  int y, x;

  // amount of words per line 
  Vec *words_per_line; // keeps the index at which the line ends

  // amount of chars per line 
  Vec *chars_per_line;

} Renderer;

Renderer *renderer_init(void);

void renderer_update(Renderer *renderer, char **word_list, int size);

void render(Renderer *renderer);

#endif // __TAIPO__RENDERER_H__
