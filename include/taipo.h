#ifndef __TAIPO_H__
#define __TAIPO_H__

#include "word_generator.h"

typedef struct Taipo {
  int current; // current word that user is typing
  Generator *gen;
} Taipo;

Taipo *init_taipo(void);

void free_taipo(Taipo *taipo);

#endif // __TAIPO_H__
