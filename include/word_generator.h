#ifndef __TAIPO__WORD_GENERATOR_H__
#define __TAIPO__WORD_GENERATOR_H__
#include "ext/int.h"

typedef struct Generator {
  // stores the current list of words
  const char **words;

  // number of words to be generated
  int nwords;
} Generator;

// init
Generator *init_generator(void);

// generate n random words
void generate_words(Generator *gen, int n);

// free words
void free_words(const char **words, int nwords);

// free generator
void free_generator(Generator *gen);


#endif // __TAIPO__WORD_GENERATOR_H__
