#include "word_generator.h"
#include "english_words.h"
#include "misc.h"
#include "vec.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

/*
 * NOTE:
 * need to tweak rendering to support multiple lines.
 * currently it partially supports multiple lines.
 */

void generate_words(Generator *gen) {
  // allocate and store random words
  gen->words = (const char **)malloc(gen->nwords * sizeof(const char *));
  for (int i = 0; i < gen->nwords; i++) {
    gen->words[i] = strdup(english[rand() % 200]);
  }
}

Generator *init_generator(int nwords) {
  Generator *gen = (Generator *)malloc(sizeof(Generator));
  gen->nwords = nwords;
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
