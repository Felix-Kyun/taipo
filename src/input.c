#include "input.h"
#include "cstring_vec.h"
#include "renderer.h"
#include <ncurses.h>

#define VALIDATE(ch) (ch >= 32 /* space */ && ch <= 126 /* ~ */)

Input *input_init(Renderer *renderer) {
  Input *input = (Input *)malloc(sizeof(Input));
  input->input = cstring_new();
  input->renderer = renderer;

  return input;
}

void input_free(Input *input) {
  cstring_free(input->input);
  free(input);
}

void input_update(Input *input, int ch) {
  CString *current_word = cstring_vec_get(input->renderer->word_list,
                                          input->renderer->current_word_index);
  // CString *current_word = cstring_from("hello");
  int do_render = 0; // 1 to render

  if (ch == KEY_BACKSPACE) {
    // clear();
    if (input->input->size > 0) input->input->size--;
    do_render = 1;
  } else if (ch == ' ' || ch == '\n') {
    if (cstring_cmp(input->input, current_word)) {  // correct
      input->renderer->correct_word_map[input->renderer->current_word_index] =
          1;
    } else { // incorrect
      input->renderer->correct_word_map[input->renderer->current_word_index] =
          2;
    }

    input->renderer->current_word_index++;

    cstring_free(input->input);
    input->input = cstring_new();
    do_render = 1;
  } else if (VALIDATE(ch)) {
    cstring_append_char(input->input, ch);
    do_render = 1;
  }

  if (do_render) {
    render(input->renderer);
    render_input_box(input);
    refresh();
  }
}

void render_input_box(Input *input) {

  input->box_y = input->renderer->y - 2;
  input->box_x = (input->renderer->x - input->input->size) / 2;

  move(input->box_y, input->box_x);
  for (int i = 0; i < input->input->size; i++) {
    addch(input->input->str[i]);
  }
  // printw("%s", cstring_get(input->input));

  refresh();
}
