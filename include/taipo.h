#ifndef __TAIPO_H__
#define __TAIPO_H__

#include "renderer.h"
#include "word_generator.h"

typedef struct Taipo {
  // for generating words
  Generator *gen;
  
  // handles rendering the words
  Renderer *renderer;
} Taipo;

Taipo *init_taipo(void);

void free_taipo(Taipo *taipo);

#endif // __TAIPO_H__
