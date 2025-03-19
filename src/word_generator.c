#include "word_generator.h"
#include "english_words.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void generate_words(Generator *gen, int n) {
  // allocate and store random words
  gen->nwords = n;
  gen->words = (const char **)malloc(n * sizeof(const char *));
  for (int i = 0; i < gen->nwords; i++) {
    gen->words[i] = strdup(english[rand() % 200]);
  }
}

Generator *init_generator(void) {
  Generator *gen = (Generator *)malloc(sizeof(Generator));
  gen->words = NULL;

  return gen;
}

void free_generator(Generator *gen) {
  if (gen->words != NULL)
    free_words(gen->words, gen->nwords);
  free(gen);
}

void free_words(const char **words, int nwords) {
  for (int i = 0; i < nwords; i++) {
    free((void *)words[i]);
  }

  free((void *)words);
}
