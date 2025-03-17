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
    gen->length_words[i] = strlen(gen->words[i]) + 1; // include space
  }

  // get screen dimensions
  int screen_x, screen_y;
  getmaxyx(stdscr, screen_y, screen_x);
  screen_x -= 2; // adjust for border
  screen_y -= 2; // adjust for border

  // calculate the number of words per line
  gen->words_line = words_per_line(gen->length_words, gen->nwords, screen_x);

  // calculate the starting x position of each line
  gen->start_x = (int *)malloc(gen->words_line->size * sizeof(int));
  int index = 0;
  for (size_t i = 0; i < gen->words_line->size; i++) {
    gen->start_x[i] =
        (screen_x -
         char_per_line(gen->length_words, index, int_vec_get(gen->words_line, i))) /
        2;
    index += int_vec_get(gen->words_line, i);
  }

  // store the starting y position
  gen->start_y = (screen_y - gen->words_line->size) / 2;
}

void clear_words(Generator *gen) {

  int index = 0;
  for (int i = 0; i < ((int)gen->words_line->size); i++) {
    move(gen->start_y + i, gen->start_x[i]);
    int char_count =
        char_per_line(gen->length_words, index, int_vec_get(gen->words_line, i));
    for (int j = 0; j < char_count; j++) waddch(stdscr, ' ');
    index += int_vec_get(gen->words_line, i);
  }
}

void display_words(Generator *gen) {
  attron(COLOR_PAIR(1));
  move(gen->start_y, gen->start_x[0]);

  for (size_t i = 0; i < gen->words_line->size; i++) {
    move(gen->start_y + i, gen->start_x[i]);
    for (int j = 0; j < int_vec_get(gen->words_line, i); j++) {
      printw("%s ", gen->words[j]);
    }
  }

  move(gen->start_y, gen->start_x[0]);
  attroff(COLOR_PAIR(1));
}

Generator *init_generator(int nwords) {
  Generator *gen = (Generator *)malloc(sizeof(Generator));
  gen->length_words = (int *)malloc(nwords * sizeof(int));
  gen->nwords = nwords;
  gen->words = NULL;

  return gen;
}

void free_generator(Generator *gen) {
  free_words(gen->words, gen->nwords);
  free(gen->length_words);
  vec_destroy(gen->words_line);
  free(gen->start_x);
  free(gen);
}

void free_words(const char **words, int nwords) {
  for (int i = 0; i < nwords; i++) {
    free((void *)words[i]);
  }

  free((void *)words);
}
