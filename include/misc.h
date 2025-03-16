#ifndef __TAIPO__MISC_H__
#define __TAIPO__MISC_H__

#include "vec.h"
int sum_int_array(int *arr, int n);

// returns a vector of words required per line
Vec *words_per_line(int *length_words, int nwords, int screen_x);

// returns the number of characters required per line
int char_per_line(int *length_words, int start, int n);

#endif // __TAIPO__MISC_H__
