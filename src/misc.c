#include "misc.h"
#include "ext/int.h"
#include "word_generator.h"
#include <ncurses.h>

int sum_int_array(int *arr, int n) {
  int sum = 0;

  for (int i = 0; i < n; i++) {
    sum += arr[i];
  }

  return sum;
}

Vec *words_per_line(int *length_words, int nwords, int screen_x) {
  Vec *words_line = vec_init();

  int index = 0;
  while (index < nwords) {
    int sum = 0;
    int count = 0;
    while (index < nwords && sum + length_words[index] < screen_x) {
      sum += length_words[index];
      index++;
      count ++;
    }
    int_vec_push_back(words_line, count);
  }

  return words_line;
}

int char_per_line(int *length_words, int start, int n) {
  int sum = 0;
  for (int i = start; i < start + n; i++) {
    sum += length_words[i];
  }
  return sum;
}

