#include "input.h"
#include "cstring_vec.h"
#include "events.h"
#include "hud.h"
#include "misc.h"
#include "renderer.h"
#include <ncurses.h>

#define VALIDATE(ch) (ch >= 32 /* space */ && ch <= 126 /* ~ */)

extern Game_event event;

Input *input_init(Renderer *renderer) {
  Input *input = (Input *)malloc(sizeof(Input));
  input->input = cstring_new();
  input->renderer = renderer;
  input->hud = hud_init();

  return input;
}

void input_free(Input *input) {
  cstring_free(input->input);
  free(input);
}

void input_update(Input *input, int ch) {
  CString *current_word = cstring_vec_get(input->renderer->word_list,
                                          input->renderer->current_word_index);

  if (ch == KEY_BACKSPACE) {

    if (input->input->size > 0)
      input->input->size--;

    event |= RENDER;

  } else if (ch == ' ' || ch == '\n') {

    // check if the typed word is correct
    if (cstring_cmp(input->input, current_word)) { // correct

      input->renderer->correct_word_map[input->renderer->current_word_index] =
          1;
      hud_correct(input->hud);

    } else { // incorrect

      input->renderer->correct_word_map[input->renderer->current_word_index] =
          2;
      hud_incorrect(input->hud);
    }

    if (input->renderer->current_word_index <
        (int)input->renderer->word_list->size - 1) {
      input->renderer->current_word_index++;
    } else {
      event |= END;
    }

    cstring_free(input->input);
    input->input = cstring_new();

    event |= RENDER;
  } else if (VALIDATE(ch)) {

    if (event & UNKNOWN) {
      event |= START; // fire event
    }

    cstring_append_char(input->input, ch);
    event |= RENDER;
  }

  // time ends, fire game stop event
  if (get_seconds() - input->hud->time >= 15.0) {
    event |= END;
  }

  if (event & RENDER) {
    event ^= RENDER;
    render(input->renderer);
    render_hud(input->hud);
    render_input_box(input);
    refresh();
  }

  // event handler
  if (event & START) {
    // consume the event
    event ^= START;

    hud_update_time(input->hud);
  }

  if (event & END) {
    // consume the event
    event = UNKNOWN;

    // end the game
    show_end_screen(input->hud);
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
