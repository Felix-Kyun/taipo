#ifndef __TAIPO__WORD_GENERATOR_H__
#define __TAIPO__WORD_GENERATOR_H__
#include "ext/int.h"

typedef struct Generator {
  // stores the current list of words
  const char **words;

  // stores the length of each word
  int *length_words;

  // stores the number of words per line
  Vec *words_line;

  // stores the starting x position of each line
  int *start_x;

  // stores the starting y position
  int start_y;

  // number of words to be generated
  int nwords;
} Generator;

// init
Generator *init_generator(int nwords);

// generate n random words
void generate_words(Generator *gen);

// display words
void display_words(Generator *gen);

// clear screen
void clear_words(Generator *gen);

// free words
void free_words(const char **words, int nwords);

// free generator
void free_generator(Generator *gen);


#endif // __TAIPO__WORD_GENERATOR_H__
