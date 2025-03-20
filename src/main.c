#include "events.h"
#include "input.h"
#include "renderer.h"
#include "taipo.h"
#include <ncurses.h>
#include <unistd.h>

#define VALIDATE(ch) (ch >= 32 /* space */ && ch <= 126 /* ~ */)

Game_event event = UNKNOWN;

int main(void) {

  // init app
  Taipo *taipo = init_taipo();
  //
  // while (taipo->current < taipo->gen->nwords) {
  //   int ch = getch();
  //
  //   if (ch < 0) {
  //     usleep(1000); // sleep for 1ms
  //   }
  // }

  render(taipo->renderer);
  render_input_box(taipo->input);

  int ch = 0;
  while ((ch = getch()) != 'q') {
    input_update(taipo->input, ch);
    usleep(1000);
    if (event & END_GAME)
      break;
  }

  free_taipo(taipo);
}
