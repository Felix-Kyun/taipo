#ifndef __TAIPO__INPUT_H__
#define __TAIPO__INPUT_H__

#include "cstring.h"
#include "renderer.h"
#include "hud.h"

typedef struct Input {

  // to store the input string 
  CString *input;

  // store the renderer to automatically update the app state
  Renderer *renderer;

  // store the current position of the input box
  int box_y, box_x;

  // hud
  Hud *hud;

} Input;

Input *input_init(Renderer *renderer);

void input_update(Input *input, int ch);

void input_free(Input *input);

void render_input_box(Input *input);

#endif // __TAIPO__INPUT_H__

